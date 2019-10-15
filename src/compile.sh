find . -type f -name *.cpp -exec cp {} . \;
find . -type f -name *.h -exec cp {} . \;
make
rm *.cpp
rm *.h
rm *.dep
