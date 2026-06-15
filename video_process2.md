침식: 흰색 객체를 깎아내는 연산
팽창: 흰색 객체를 키우는 연산

1. 오프닝 필터 Opening Filter

오프닝 = 침식 → 팽창

작은 밝은 점, 작은 밝은 잡음, 가느다란 돌출부를 제거하는 필터
흰색 잡음이나 작은 밝은 물체가 구조요소보다 작으면 사라진다

2. 클로징 필터 Closing Filter

클로징 = 팽창 → 침식

작은 어두운 구멍, 작은 검은 점, 끊어진 틈을 메우는 필터
밝은 객체 안이나 사이에 있는 작은 검은 부분이 메워진다

Huffman Coding은 심볼의 발생 확률을 이용하여 가변 길이 코드를 만드는 압축 방법이다. 발생 확률이 높은 심볼에는 짧은 코드를, 발생 확률이 낮은 심볼에는 긴 코드를 부여하여 평균 코드 길이를 줄인다.

> JPEG overview 
8×8 blocks → DCT → Quantize → Run-length coding → Huffman coding

> DCT
픽셀값을 주파수 성분으로 바꾸는 과정

- DC coefficient와 63개의 AC coefficients로 구성

쓰는이유? -> 중요한 정보 저주파쪽 몰림, 저주파 성분을 보존하고 고주파 성분은 줄여 압축 효율 높임.

> Run-Length-Code

RLC는 반복되는 0을 “개수”로 줄이는 것이고, Huffman Coding은 그 결과 심볼을 “짧은 비트 코드”로 바꾸는 것이다.