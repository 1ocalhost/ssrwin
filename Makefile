default:
	@which i686-w64-mingw32-gcc >/dev/null || sudo apt install gcc-mingw-w64
	@which g++ >/dev/null || sudo apt install g++  # for using cmake
	@which cmake >/dev/null || sudo apt install cmake
	@mkdir -p out && cd out && cmake .. && make

clean:
	@rm -rf out/*
