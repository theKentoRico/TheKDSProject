$(KDS_ADDTOPATH) = TRUE
kds: *.cpp *.hpp Makefile build_systems/make/Makefile
	g++ kds.cpp -o kds -g
ifeq (KDS_ADDTOPATH, TRUE) # if addtopath is enabled
	cp kds /usr/bin/kds
	rm -rf ./kds
endif
