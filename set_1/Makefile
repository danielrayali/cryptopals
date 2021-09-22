all: challenge_1 challenge_2 challenge_3

challenge_1: challenge_1.cc hex_encoder.h base64_encoder.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_2: challenge_2.cc hex_encoder.h xor.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_3: challenge_3.cc hex_encoder.h xor.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

clean:
	rm -rf challenge_1 challenge_2 challenge_3
