

# reads words from stdin and autocomple first argument
autocomp word='t':
  @ ./autocomp {{word}} < words.txt

# build source
build:
  gcc main.c -o autocomp
