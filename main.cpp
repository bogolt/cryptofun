#include <iostream>

unsigned char hashString(const std::string& s) {
	unsigned char hashResult = 0;
	for (auto ch: s) {
		hashResult ^= ch;
	}
	return hashResult;
}

std::string encrypt(const std::string& src, unsigned char key) {
	std::string encryptedString;
	for (auto s: src) {
		encryptedString += s ^ key;
	}
	return encryptedString;
}

std::string decrypt(const std::string& encryptedString, unsigned char key) {
	return encrypt(encryptedString, key);
}

// TESTING
void testUnequalHash(const std::string& a, const std::string& b) {
	if (a==b) {
		printf("not equal strings expected\n");
		return;
	}

	auto hashA = hashString(a);
	auto hashB = hashString(b);
	if (hashA == hashB) {
		printf("hash collision: %s and %s both produce: %c\n", a.c_str(), b.c_str(), hashA);
		return;
	}
	printf("unequal hash ok\n");
}

void testEncrypt(const std::string& text, unsigned char key) {
	auto encryptedText = encrypt(text, key);
	auto decryptedText = decrypt(encryptedText, key);
	if (text != decryptedText) {
		printf("decrypt back failed! %s => %s => %s\n", text.c_str(), encryptedText.c_str(), decryptedText.c_str());
		return;
	}
	if (encryptedText == decryptedText) {
		printf("such a weak encryption you have\n");
		return;
	}

	auto badDecryptedText = decrypt(encryptedText, key+1);
	auto badDecryptedText2 = decrypt(encryptedText, key-1);

	if (text == badDecryptedText) {
		printf("such a weak encryption you have (key differ by +1 )\n");
		return;
	}

	if (text == badDecryptedText2) {
		printf("such a weak encryption you have (key differ by -1 )\n");
		return;
	}

	printf("encrypt/decrypt ok\n");
}

using namespace std;

int main()
{
	testUnequalHash("abcd", "abc");
	testUnequalHash("abd", "abc");
	testUnequalHash("a", "b");
	testUnequalHash("abcd123", "123abc");


	// crypto
	testEncrypt("Friend!", '5');
	return 0;
}
