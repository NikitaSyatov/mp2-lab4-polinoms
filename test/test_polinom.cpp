//test for Polinom and List
#include "../gtest/gtest.h"
#include "../include/polinom.h"

TEST(class_List, can_make_List)
{
	ASSERT_NO_THROW(List());
}

TEST(class_List, can_push_back)
{
	List a;
	ASSERT_NO_THROW(a.push_back(2, 100));
	EXPECT_EQ(2, a.GetHead()->factor);
	EXPECT_EQ(100, a.GetHead()->pow);
	ASSERT_NO_THROW(a.push_back(4, 200));
	EXPECT_EQ(4, a.GetHead()->pNext->factor);
	EXPECT_EQ(200, a.GetHead()->pNext->pow);
}

TEST(class_List, can_getHead)
{
	List a;
	a.push_back(2,100);
	ASSERT_NO_THROW(a.GetHead());
}

TEST(class_List, can_Sort)
{
	List a;
	a.push_back(4,272);
	a.push_back(3,190);
	a.push_back(5,354);
	a.Sort();
	double f = 5;
	int p = 354;
	for (Node* i = a.GetHead(); i != nullptr; i = i->pNext)
	{
		EXPECT_EQ(f, i->factor);
		EXPECT_EQ(p, i->pow);
		f--;
		p -= 82;
	}
}

TEST(class_Polinoms, can_make_correct_polinom)
{
	ASSERT_NO_THROW(Polinoms("4,6x^2y^3+z^2+xy+9"));
}

TEST(class_Polinoms, cant_make_no_correct_koef)
{
	ASSERT_ANY_THROW(Polinoms("4.6x^2"));
}

TEST(class_Polinoms, cant_make_no_correct_power)
{
	ASSERT_ANY_THROW(Polinoms("4,6x2"));
}

TEST(class_Polinoms, can_Sort_polinoms)
{
	Polinoms a("34x^2+5x^3y^4");
	Polinoms b("5x^3y^4+34x^2");
	EXPECT_TRUE(a==b);
	EXPECT_FALSE(a!=b);
}

TEST(class_Polinoms, can_copy_polinoms)
{
	Polinoms a("34x^2+5x^3y^4");
	Polinoms b = a;
	EXPECT_TRUE(Polinoms("34x^2+5x^3y^4") == b);
}

TEST(class_Polinoms, multiply_with_number_not_null)
{
	Polinoms a("7x^2+5x^3y^4");
	Polinoms b("21x^2+15x^3y^4");
	EXPECT_TRUE(b == a * 3);
}

TEST(class_Polinoms, multiply_with_null)
{
	Polinoms a("7x^2+5x^3y^4");
	Polinoms b("0");
	EXPECT_TRUE(b == a * 0);
}

TEST(class_Polinoms, summ_polinoms)
{
	Polinoms a("7x^2+5x^3y^4+7z^2");
	Polinoms b("34x^3+5x^3y^4");
	EXPECT_TRUE(Polinoms("34x^3+7x^2+10x^3y^4+7z^2") == a+b);
}

TEST(class_Polinoms, diff_polinoms)
{
	Polinoms a("7x^2+5x^3y^4+7z^2");
	Polinoms b("34x^3+7x^3y^4");
	EXPECT_TRUE(Polinoms("-34x^3+7x^2-2x^3y^4+7z^2") == a - b);
}

TEST(class_Polinoms, diff_polinoms_with_null_monoms)
{
	Polinoms a("7x^2+5x^3y^4+7z^2");
	Polinoms b("34x^3+5x^3y^4");
	EXPECT_TRUE(Polinoms("-34x^3+7x^2+7z^2") == a - b);
}

TEST(class_Polinoms, correct_multiply_with_polinoms)
{
	Polinoms a("5xyz-9");
	Polinoms b("5xyz-9");
	EXPECT_TRUE(Polinoms("25x^2y^2z^2-90xyz+81") == a * b);
}

TEST(class_Polinoms, throw_when_power_in_res_polinom_is_longest)
{
	Polinoms a("5x^8y^4z-9");
	Polinoms b("5x^5y^3z^2-9x");
	ASSERT_ANY_THROW(a*b);
}