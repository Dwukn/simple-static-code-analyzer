# Variables
source_file="main.cpp"
name="analyze"
destination="/usr/local/bin"

echo "  ____ ____   ____    _ "
echo " / ___/ ___| / ___|  / \ "
echo " \___ \___ \| |     / _ \ "
echo "  ___) |__) | |___ / ___ \ "
echo " |____/____/ \____/_/   \_\   "

# Check if the source file exists
if [ ! -f "$source_file" ]; then
    echo "Error: File '$source_file' does not exist."
    exit 1
fi
# Compile the source file
echo "Compiling '$source_file'..."
g++ -o "$name" "$source_file"

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed."
    exit 1
fi
# Run the executable
echo "Running executable '$name'..."
chmod +x ./"$name"
# Move the executable to the destination
echo "Moving '$name' to '$destination'..."
sudo mv "$name" "$destination"

# Check if the move was successful
if [ $? -eq 0 ]; then
    echo "Successfully installed."
else
    echo "Installation failed."
    exit 1
fi
