#!/bin/bash

##
# @file
# Updates the copyrights in all C++ source files to match latest Git commit.
#
# Run while CWD is the project root.
#
# Authored with some help from ChatGPT :)
################################################################################

set -euo pipefail

##
# Extracts starting and ending copyright years from the first line of a file.
#
# If the given file has a copyright in the first line, it is parsed and the
# starting and ending years of the copyright are echoed back, delimited by a
# dash. If there is only a single year and not a range of years, that year is
# echoed back without a delimiter.
#
# This automatically handles files that have a UTF-8 BOM.
#
# @param $1
#   The path to the file from which the copyrights should be extracted.
#
# @return
#   - 0 if the copyright line was parsed and years were extracted successfully.
#   - 1 if the copyright line could not be parsed or the file was empty.
#
extract_current_copyrights() {
	local filename="$1"

	if [[ -s "$filename" ]]; then
		local first_line="$(sed '1s/^\xEF\xBB\xBF//' "$filename" | head -n 1)"

		if [[ "$first_line" =~ ^\/\/.*Copyright\ ([0-9]{4})(-([0-9]{4}))? ]]; then
			local start_year="${BASH_REMATCH[1]}"
			local end_year="${BASH_REMATCH[3]}"

			if [[ -z "$end_year" ]]; then
				echo "$start_year"
			else
				echo "$start_year-$end_year"
			fi

			return 0
		fi
	fi

	return 1
}

##
# Updates the copyright ranges in the given file, if applicable.
#
# @param $1
#   The path to the file to update.
#
process_file() {
	local filename="${1}"
	local current_range

	current_range=$(extract_current_copyrights "${filename}" || echo "")

	if [[ -n "${current_range}" ]]; then
		local start_year="${current_range%-*}"
		local end_year="${current_range#*-}"

		latest_mod_year="$(git log --pretty=format:%ad --date=format:%Y --max-count=1 "${filename}")"

		if [[ "${latest_mod_year}" -gt "${end_year}" ]]; then
			echo "${filename}: Updating copyright from '${end_year}' to '${latest_mod_year}'."

			if [[ "${start_year}" == "${latest_mod_year}" ]]; then
				new_copyright_years="${latest_mod_year}"
			else
				new_copyright_years="${start_year}-${latest_mod_year}"
			fi

			sed -i "1s/\(.*Copyright\) [0-9]\{4\}\(-[0-9]\{4\}\)\{0,1\}\(.*\)/\1 ${new_copyright_years}\3/" "${filename}"
		fi

	elif [[ -f "${filename}" ]]; then
		echo "${filename}: Could not find copyright line."

	else
		echo "${filename}: Skipped (file deleted in branch)."
	fi
}

# Get the list of modified files in the feature branch relative to main
modified_files=$(git diff --name-only main...HEAD | grep -E "\.(h|hpp|c|cpp|cc|cxx)$")

# Update copyright lines of all changed files.
for filename in $modified_files; do
	process_file "${filename}"
done
