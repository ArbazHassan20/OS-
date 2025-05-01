# Prompt user for filename
echo "Enter the filename:"
read filename

# Check if file exists
if [ -f "$filename" ]; then
	# count and display number of lines
	line_count=$(wc -l < "$filename")
	echo "The file '$filename' has $line_count lines."
else
	echo "Error: File '$filename' not found."
fi
