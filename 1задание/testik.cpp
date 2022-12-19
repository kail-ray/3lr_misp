#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/111111/1_2lr/modAlphaCipher.h"
#include "/home/stud/C++Projects/111111/1_2lr/modAlphaCipher.cpp"
using namespace std;


SUITE(KeyTest) //макрос для создания набора тестов
{
    TEST(ValidKey) {//макрос для создания одного теста
        CHECK_EQUAL("АБВАБ", modAlphaCipher("АБВ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("АБВГД",modAlphaCipher("АБВГДЕЁЖ").encrypt("ААААА"));//макрос для проверки полученного результата и ожидаемого
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("АБВАБ", modAlphaCipher("абв").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"), cipher_error);// марос для проверки на возбуждение исключения
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("А,Б"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("А Б"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"), cipher_error);
    }
}
struct KeyB_fixture {//слово struct использовано вместо class чтобы сделать все
    modAlphaCipher* p;//члены класса открытыми
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");//класс, который в конструкторе создает динамический экземпляр шифратора с ключом «B», а в
    }                               //деструкторе — уничтожает:
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {//использовать вместо макроса TEST потому что ключ один
        CHECK_EQUAL("НБНБНЬМБСБНФ", p->encrypt("МАМАМЫЛАРАМУ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("НБНБНЬМБСБНФ", p->encrypt("мамамылараму"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("НБНБНЬМБСБНФ", p->encrypt("Мама мыла раму"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123123123"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ЛЯЛЯЛЪКЯПЯЛТ",modAlphaCipher("Я").encrypt("МАМАМЫЛАРАМУ"));
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("МАМАМЫЛАРАМУ", p->decrypt("НБНБНЬМБСБНФ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p -> decrypt("нБНБНЬМБСБНФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("НБНБ НЬМБ СБНФ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p -> decrypt("123123123"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p -> decrypt("НБНБ,НЬМБСБНФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("МАМАМЫЛАРАМУ",modAlphaCipher("Я").decrypt("ЛЯЛЯЛЪКЯПЯЛТ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
