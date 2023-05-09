if [ ! -d "build/" ]; then
	mkdir build
fi

if [ ! -d "sandbox/build" ]; then
	mkdir sandbox/build/
fi

cd sandbox/build
cmake .. && make
cd ../../

if [ ! -f "build/compile_commands.json" ]; then
	ln sandbox/build/compile_commands.json build/compile_commands.json
fi
