all: challenge_1

challenge_1: challenge_1.cc hex_encoder.h base64_encoder.h
	clang -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++ -lfmt

clean:
	rm -rf challenge_1
