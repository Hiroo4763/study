# 4장

## 내장 함수

- ABS() - 절대값 
- ROUND() - 반올림
- REPLACE() - 문자열 치환
- LEN() - 글자 수 세기
- SUBSTRING() - 지정한 길이만클 문자열 반환
- DATEADD() - 원하는 날짜만큼 날짜를 더함
- SYSDATETIME() 현재 시간을 반환

## NULL 값 처리

NULL + 숫자 = NULL
NULL이 포함된 행은 집계에서 빠진다.
NULL 값을 찾을 땐 IS NULL을 이용한다.

## 뷰

```
CREATE VIEW [뷰이름] AS SELECT [셀렉목록]
```

## 인덱스
클러스터 인덱스: 데이터 자체가 정렬된 인덱스(범위 검색에 유리)
비클러스터 인덱스: 데이터는 그대로 두고 인덱스만 따로 둔 구조(다중 검색 조건에 유리)

``` sql
CREATE INDEX ix_Book ON Book (bookname);
```

``` sql
CREATE CLUSTERED INDEX cix_Customer ON Customer (name)
```

인덱스 삭제

``` sql
DROP INDEX ix_Book ON Book;
```

- 인덱스는 검색 속도를 높이기 위해 별도로 만든 정렬된 데이터 구조
- 인덱스를 사용하면 검색·조인·정렬 속도가 빨라져 질의 성능이 향상된다.
- 인덱스는 저장 공간을 더 사용하고, 삽입·수정·삭제 성능을 저하시킨다.

# 프로시저

``` sql
CREATE PROCEDURE [프로시져명] ([@파라미터])
AS
BEGIN
    [쿼리명]
END
```

Book 테이블에 한 개의 튜플을 삽입하는 프로시저를 작성하시오.
```sql
USE madang 
DROP PROCEDURE InsertBook
GO -- 문장을 끊는 표시

CREATE PROCEDURE InsertBook(@BookID INT, @BookName NVARCHAR(40), @Publisher NVARCHAR(40), @Price INT)
AS 
BEGIN
    INSERT INTO dbo.Book(bookid, bookname, publisher, price)
    VALUES (@BookID, @BookName, @Publisher, @Price);
END
GO

EXEC InsertBook 12, "스포츠과학", "마당과학서적", 25000
SELECT * FROM Book;
GO
```

Book 테이블에 저장된 도서의 평균 가격을 반환하는 프로시저를 작성하시오
``` sql
USE madang
DROP PROCEDURE AveragePrice
GO

CREATE PROCEDURE AveragePrice(@AverageVal INT OUTPUT)AS
BEGIN
	SET @AverageVal = (SELECT AVG(price) 
						FROM Book
						WHERE price IS NOT NULL);
END
GO

DECLARE @Avg INT
EXEC AveragePrice @AverageVal = @Avg OUTPUT
SELECT @Avg '책값 평균'
GO
```

# 트리거

트리거는 테이블에서 특정 이벤트(INSERT/UPDATE/DELETE)가 발생할 때 자동 실행되는 프로시저다. (ex. Book이 삭제될 때 로그를 자동으로 남기고 싶다.)

``` sql
CREATE TRIGGER 트리거명 ON 테이블명 [AFTER INSERT, UPDATE, DELETE] 
AS
BEGIN
    -- 트리거 내용
END;
```

# 사용자 정의 함수
- 함수는 “계산 전용”, 프로시저는 “작업 전용”.
- 데이터 변경(INSERT/UPDATE/DELETE) 불가
- 반드시 값 반환

```sql
CREATE FUNCTION 함수명(@변수 INT)
RETURNS INT
AS
BEGIN
    RETURN @변수;
END;
```

# 6장

## ER 다이어그램

*직사각형 - 강한 개체 타입*
- 자기 혼자서도 존재할 수 있는 개체
- 기본키(PK)를 스스로 가진다
- EX) 학생, 상품, 고객

*이중 직사각형 - 약한 개체 타입*
- 혼자서는 구별될 수 없는 개체
- 고유한 기본키가 없음, 다른 개체의 PK를 사용해야 구별됨
- EX) 수강(학생 + 과목)

*동그라미 - 단순 속성*
- 더 이상 분해 불가능한 속성

*동그라미 - 복합 속성*
- 독립적인 의미를 가진 속성으로 분해할 수 있는 속성
-         주소
       시      동

*동그라미 - 단일값 속성*
- 값이 단일임

*이중 동글라미 - 다중값 속성*
- 값이 다중값임
- 학위(학사, 석사)

*동그라미 - 저장 속성*
- 다른 속성의 영향 없이 단독으로 저장되는 속성

*동그라미 - 유도 속성*
- 다른 저장 속성으로부터 유도된 속성
- 생년월일 - 나이

*마름모 - 관계 타입*

### 참여 제약조건
: 중복 구조 때문에 추가할 수 없거나, 불필요한 데이터를 같이 넣어야 하는 문제.
*줄 두개 - 전체 참여*
*줄 한개 - 부분 참여*

역할은 뭐냐 대체

# 7장

## 이상현상

잘못된 데이터베이스 설계로 생기는 현상인듯

1. 삭제이상
: 원래 지울 필요 없는 중요한 정보까지 함께 삭제되는 문제.

2. 삽입이상
: 중복 구조 때문에 추가할 수 없거나, 불필요한 데이터를 같이 넣어야 하는 문제.

3. 수정이상
: 하나만 수정해도 나머지는 그대로 남아 데이터 불일치가 생기는 문제.


결정자 : 다른 속성의 값을 결정해 주는 속성 <---????

## 정규화

릴레이션을 분해해서 이상현상을 없애는 과정

### 제 1정규형
속성값이 유일하도록 바꾸는 것

EX) 고객취미들(이름, 취미들) -> 고객취미(이름, 취미)

### 제 2정규형
기본키가 복합키일 때, 기본키의 일부만으로 일반 속성이 결정되지 않는 것

EX)학번	과목번호 학생이름 과목명 성적
기본키: (학번, 과목번호)

기본키의 일부가 일부 속성을 결정지을 수 있기때문에 2NF 위반

### 제 3정규형
제2정규형을 만족하고, 기본키가 아닌 속성 간의 이행적 함수적 종속이 없는 관계

### BCNF 정규형
모든 결정자가 후보키인 관계
다른 값을 결정하는 애는 반드시 키여야 한다