all: challenge_1 challenge_2

challenge_1: challenge_1.cc hex_encoder.h base64_encoder.h
	clang -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_2: challenge_2.cc
	clang -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

clean:
	rm -rf challenge_1 challenge_2
