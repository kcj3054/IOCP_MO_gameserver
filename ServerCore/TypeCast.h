#pragma once


#pragma region TypeList

 template<typename... T>
 struct TypeList;

 template<typename T, typename U>
 struct TypeList<T, U>
 {
	 using Head = T;
	 using Tail = U;
 };

 /*
*
* TypeList<Mage, TypeList<Knight, Archer>>::Head T1;
* TypeList<Mage, TypeList<Knight, Archer>>::Tail T2;
* TypeList<Mage, TypeList<Knight, Archer>>::Tail::Tail T3;
* 
* ���� �ٸ� Ÿ�Ե��� �ϳ��� List�� Vector�� ���� �� �ִ�. �Ϲ����� stl�� ������ Ÿ�Ե鸸 ���� �����ϴ� 
* 
* �̷������� �����ϸ� compileTime�� �����Ǵ� compile �Ŀ� ���� ������ �δ��� ����. 
*/
 template<typename T, typename... U>
 struct TypeList<T, U...>
 {
	 using Head = T;
	 using Tail = TypeList<U...>;
 };

#pragma endregion

#pragma region Length

 // enum �� �����ϰ� ������ Ÿ�Կ� �����Ǵ� ���̴� 
 template<typename T>
 struct Length;

 //��������� ȣ�� �� �� ���� ���� �� + 0���Ѵٴ� �ǹ� 
 template<>
 struct Length<TypeList<>>
 {
	 enum { value = 0 };
 };

 /*
 * ex : 
 * int len1 = Length<TypeList<Mage, Knight>>::value;
 * int len2 = Length<TypeList<Mange, Knight, Archer>>::value;
 * 
 * -> 1 + Length<Knight, Archer>
 * -> 1 + 1 + 1 + LengthTypeList<>
 * -> 1 + 1 + 1 + 0 -> 3
 */
 template<typename T, typename... U>
 struct Length <TypeList<T, U...>>
 {
	 enum { value = 1 + Length<TypeList<U...>>::value };
 };

#pragma endregion


#pragma region TypeAt

 /*
 * 0, 1, 2��° �ε��������� Ÿ���� � ������ Ȯ���� �� �ִ� 
 * 
 * ex : 
 * using TL = TypeList<Mange, Knight, Archer>;
 * TypeAt<TL, 0>::Result whilAMI6; -> 0��°��� Result�� Head�̴�. 
 * 
 * 0���� �ƴ� ���� template�� ��������� ȣ��ȴ� 
 */
 template<typename TL, int index>
 struct TypeAt;

 template<typename Head, typename... Tail>
 struct TypeAt<TypeList<Head, Tail...>, 0>
 {
	 using Result = Head;
 };

 template<typename Head, typename... Tail, int index>
 struct TypeAt<TypeList<Head, Tail...>, index>
 {
	 // Head -> �������� Tail�� ���� ó���� �ٽ� Head�� �Ǹ鼭 ��Ͱ��ȴ�. �̶� index�� -1�̵ȴ�.
	 // index�� 0�϶� �ش� Ÿ���� ����� �� �ִ� 
	 using Result = typename TypeAt<TypeList<Tail...>, index - 1>::Result;
 };
#pragma endregion

#pragma region Conversion

 template<typename From, typename To>
 class Conversion
 {
 private:
	 using Small = __int8;
	 using Big = __int32;

	 // // To Ÿ���� ���� ��, Small ��ȯ
	 static Small Test(const To&) { return 0; }

	 // ��Ÿ ��� ��� Big ��ȯ
	 static Big Test(...) { return 0; }

	 // static From MakeFrom() { return 0; } // From Ÿ���� ��ȯ
	 static From MakeFrom() { return 0; }
 public:
	 enum
	 {
		 // Test(MakeFrom()) -> Test(From) From Ÿ���� Test���ڷ� �ѱ�� ToŸ���� ���� ��쿡�� Small�� ��ȯ�ǰ� 
		 // �ƴ� ��쿡�� Big���� ��ȯ�ȴ� 
		 exist = sizeof(Test(MakeFrom()) == sizeof(Small));
	 };
 };

#pragma endregion