all: challenge_1 challenge_2 challenge_3 challenge_4 challenge_5 xor challenge_6

challenge_1: challenge_1.cc hex_encoder.h base64.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_2: challenge_2.cc hex_encoder.h xor.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_3: challenge_3.cc hex_encoder.h xor.h xor_key_finder.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_4: challenge_4.cc hex_encoder.h xor.h xor_key_finder.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_5: challenge_5.cc hex_encoder.h xor.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

xor: xor_main.cc hex_encoder.h xor.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< -lstdc++

challenge_6: challenge_6.cc bitset.h bitset.cc base64.h
	clang -g -Wall -Wextra -Werror -std=c++2a -o $@ $< bitset.cc -lstdc++

clean:
	rm -rf challenge_1 challenge_2 challenge_3 challenge_4 challenge_5 xor challenge_6
