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
* 서로 다른 타입들을 하나의 List나 Vector에 넣을 수 있다. 일반적인 stl은 동일한 타입들만 삽입 가능하다 
* 
* 이런식으로 관리하면 compileTime에 결정되니 compile 후에 전혀 서버에 부담이 없다. 
*/
 template<typename T, typename... U>
 struct TypeList<T, U...>
 {
	 using Head = T;
	 using Tail = TypeList<U...>;
 };

#pragma endregion

#pragma region Length

 // enum 도 동일하게 컴파일 타입에 결정되는 것이다 
 template<typename T>
 struct Length;

 //재귀적으로 호출 후 빈 값이 됐을 때 + 0을한다는 의미 
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
 * 0, 1, 2번째 인덱스에서의 타입은 어떤 것인지 확인할 수 있다 
 * 
 * ex : 
 * using TL = TypeList<Mange, Knight, Archer>;
 * TypeAt<TL, 0>::Result whilAMI6; -> 0번째라면 Result가 Head이다. 
 * 
 * 0번이 아닐 때는 template가 재귀적으로 호출된다 
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
	 // Head -> 다음에는 Tail의 가장 처음이 다시 Head가 되면서 재귀가된다. 이때 index는 -1이된다.
	 // index가 0일때 해당 타입을 계산할 수 있다 
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

	 // // To 타입을 받을 때, Small 반환
	 static Small Test(const To&) { return 0; }

	 // 기타 모든 경우 Big 반환
	 static Big Test(...) { return 0; }

	 // static From MakeFrom() { return 0; } // From 타입을 반환
	 static From MakeFrom() { return 0; }
 public:
	 enum
	 {
		 // Test(MakeFrom()) -> Test(From) From 타입을 Test인자로 넘긴다 To타입이 받을 경우에는 Small로 반환되고 
		 // 아닌 경우에는 Big으로 변환된다 
		 exist = sizeof(Test(MakeFrom()) == sizeof(Small));
	 };
 };

#pragma endregion