#include "Contact.h"
#include <cassert>
#include <sstream>

// ---------------- Test helper ----------------

int totalTests = 0;
int passedTests = 0;

void checkTest(const string& testName, bool condition) {
    totalTests++;
    if (condition) {
        passedTests++;
        cout << "[PASSED] " << testName << endl;
    } else {
        cout << "[FAILED] " << testName << endl;
    }
}

// ---------------- Test 1: Constructor ----------------

void testConstructors() {
    cout << "\n===== Test Constructor =====" << endl;

    // Dữ liệu hợp lệ
    Contact c1("Nguyen Van A", "0912345678", "Ban be");
    checkTest("Constructor voi du lieu hop le - name",
              c1.getName() == "Nguyen Van A");
    checkTest("Constructor voi du lieu hop le - phone",
              c1.getPhone() == "0912345678");
    checkTest("Constructor voi du lieu hop le - relationship",
              c1.getRelationship() == "Ban be");

    // Constructor mặc định
    Contact c2;
    checkTest("Constructor mac dinh - name rong",
              c2.getName() == "");
    checkTest("Constructor mac dinh - phone rong",
              c2.getPhone() == "");
    checkTest("Constructor mac dinh - relationship rong",
              c2.getRelationship() == "");

    // Dữ liệu không hợp lệ: phone sai, name rỗng
    cout << "-- Truong hop du lieu khong hop le (mong doi in ra thong bao loi ben duoi) --" << endl;
    Contact c3("", "123", "Gia dinh");
    checkTest("Constructor voi name rong -> giu gia tri mac dinh",
              c3.getName() == "");
    checkTest("Constructor voi phone sai -> giu gia tri mac dinh",
              c3.getPhone() == "");
    checkTest("Constructor voi relationship hop le van duoc gan",
              c3.getRelationship() == "Gia dinh");
}

// ---------------- Test 2: Validation ----------------

void testValidation() {
    cout << "\n===== Test Validation =====" << endl;

    Contact c("Tran Thi B", "0987654321", "Dong nghiep");

    // setPhone hợp lệ
    c.setPhone("0912345678");
    checkTest("setPhone(\"0912345678\") -> hop le",
              c.getPhone() == "0912345678");

    // setPhone không hợp lệ: quá ngắn
    cout << "-- setPhone(\"123\") mong doi bao loi --" << endl;
    string oldPhone = c.getPhone();
    c.setPhone("123");
    checkTest("setPhone(\"123\") -> khong hop le, giu nguyen",
              c.getPhone() == oldPhone);

    // setPhone không hợp lệ: chứa ký tự chữ
    cout << "-- setPhone(\"09123456ab\") mong doi bao loi --" << endl;
    oldPhone = c.getPhone();
    c.setPhone("09123456ab");
    checkTest("setPhone(\"09123456ab\") -> khong hop le, giu nguyen",
              c.getPhone() == oldPhone);

    // setName rỗng
    cout << "-- setName(\"\") mong doi bao loi --" << endl;
    string oldName = c.getName();
    c.setName("");
    checkTest("setName(\"\") -> khong hop le, giu nguyen",
              c.getName() == oldName);

    // setName chỉ chứa khoảng trắng
    cout << "-- setName(\"   \") mong doi bao loi --" << endl;
    oldName = c.getName();
    c.setName("   ");
    checkTest("setName(\"   \") -> khong hop le, giu nguyen",
              c.getName() == oldName);

    // setRelationship rỗng
    cout << "-- setRelationship(\"\") mong doi bao loi --" << endl;
    string oldRelationship = c.getRelationship();
    c.setRelationship("");
    checkTest("setRelationship(\"\") -> khong hop le, giu nguyen",
              c.getRelationship() == oldRelationship);
}

// ---------------- Test 3: Getters/Setters ----------------

void testGettersSetters() {
    cout << "\n===== Test Getters/Setters =====" << endl;

    Contact c;

    c.setName("Le Van C");
    checkTest("setName hop le -> getName tra ve dung gia tri",
              c.getName() == "Le Van C");

    c.setPhone("0901234567");
    checkTest("setPhone hop le -> getPhone tra ve dung gia tri",
              c.getPhone() == "0901234567");

    c.setRelationship("Anh trai");
    checkTest("setRelationship hop le -> getRelationship tra ve dung gia tri",
              c.getRelationship() == "Anh trai");
}

// ---------------- Test 4: Display va operator<< ----------------

void testDisplayAndStreamOutput() {
    cout << "\n===== Test Display va operator<< =====" << endl;

    Contact c("Pham Thi D", "0933333333", "Hang xom");

    cout << "-- display() output: --" << endl;
    c.display();

    ostringstream oss;
    oss << c;
    string expected = "Pham Thi D, 0933333333, Hang xom";
    checkTest("operator<< xuat dung format \"name, phone, relationship\"",
              oss.str() == expected);
}

// ---------------- Test 5: Comparison ----------------

void testComparison() {
    cout << "\n===== Test Comparison =====" << endl;

    Contact c1("Alice", "0911111111", "Ban be");
    Contact c2("Bob", "0911111111", "Dong nghiep");
    Contact c3("Charlie", "0922222222", "Gia dinh");

    // operator== so sánh theo phone
    checkTest("operator== tra ve true khi cung phone",
              (c1 == c2) == true);
    checkTest("operator== tra ve false khi khac phone",
              (c1 == c3) == false);

    // operator< so sánh theo name
    checkTest("operator< tra ve true khi name dung truoc (Alice < Bob)",
              (c1 < c2) == true);
    checkTest("operator< tra ve false khi name dung sau (Charlie < Alice)",
              (c3 < c1) == false);
}

// ---------------- Main ----------------

int main() {
    testConstructors();
    testValidation();
    testGettersSetters();
    testDisplayAndStreamOutput();
    testComparison();

    cout << "\n===== Ket qua tong hop =====" << endl;
    cout << passedTests << "/" << totalTests << " test cases passed." << endl;

    if (passedTests == totalTests) {
        cout << "ALL TESTS PASSED" << endl;
    } else {
        cout << "SOME TESTS FAILED" << endl;
    }

    return (passedTests == totalTests) ? 0 : 1;
}
