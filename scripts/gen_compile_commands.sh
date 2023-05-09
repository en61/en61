if [ ! -d "build/" ]; then
	mkdir build
fi

echo "Compiling the core..."
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. 1> /dev/null
make 1> /dev/null
echo "build/compile_commands.json successfully generated!"
