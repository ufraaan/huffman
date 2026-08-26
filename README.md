# huffman

a simple huffman coding implementation in c++. encodes text into variable-length binary codes based on character frequency, then decodes it back.


## todo

- [x] encode text into huffman codes based on character frequency
- [x] decode encoded string back to original text
- [ ] pack encoded output into actual bits instead of a string of '0' and '1' chars
- [ ] add file input/output support for compressing and decompressing files
- [ ] add compression ratio stats (original vs encoded size)
- [ ] free allocated memory to avoid leaks (or use smart pointers)
