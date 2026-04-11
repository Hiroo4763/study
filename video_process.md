# 영상 향상

### 표본화와 양자화
 
아날로그 영상을 디지털로 바꾸는 과정은 세 단계로 이루어진다.
 
1. **표본화(Sampling)**: 연속 공간 좌표를 격자 형태의 불연속 좌표로 변환
2. **양자화(Quantization)**: 각 위치의 연속 밝기를 유한한 정수 레벨로 변환 (8비트 → 256단계)
3. **부호화(Encoding)**: 양자화된 값을 이진수(binary code)로 변환
 
> 시험 포인트: "아날로그 신호를 디지털로 바꾸는 과정에서 공간 좌표를 이산 신호로 바꾸는 과정은?" → **표본화(Sampling)**
 
### 영상 모델
 
>> f(x,y) = i(x,y) × r(x,y)
 
- i(x,y): 조명(illumination), 항상 양수 (i > 0)
- r(x,y): 반사율(reflectance), 0 < r < 1
 
### 해상도
 
- **공간 해상도(Spatial Resolution)**: M×N 픽셀 수. 높을수록 세밀한 영상
- **명암도 해상도(Gray Level Resolution)**: 픽셀당 비트 수. 8비트 = 256단계, 1비트 = 이진 영상
 
### 거리 함수 (3/3 출제)
 
p(x,y)와 q(s,t) 두 점 사이 거리를 세 가지로 구함.
 
- **유클리디안 거리**: De = √((x-s)² + (y-t)²)
- **City-block 거리 (D₄)**: D₄ = |x-s| + |y-t|
- **Chessboard 거리 (D₈)**: D₈ = max(|x-s|, |y-t|)
 
> 예시: p(2,3), q(5,7)
> De = √(9+16) = 5
> D₄ = 3+4 = 7
> D₈ = max(3,4) = 4
 
### 보간법 (2/3 출제)
 
영상 확대/축소/회전 시 정수 좌표가 아닌 위치의 값을 추정하는 방법.
 
- **최근접 이웃 보간**: 가장 가까운 정수 좌표의 값을 그대로 사용. 빠르지만 계단 현상 발생.
- **양선형 보간(Bilinear)**: 주변 4개 픽셀의 가중평균.
 
>> F̂(p',q') = (1-a)[(1-b)F(p,q) + bF(p,q+1)] + a[(1-b)F(p+1,q) + bF(p+1,q+1)]
 
a는 수직 방향 거리, b는 수평 방향 거리.
 
- **양3차 보간(Bicubic)**: 주변 16개 픽셀 사용. 가장 품질 좋지만 계산 비용 높음.
 
### 인간 시각 시스템
 
- **간상체(Rods)**: 약 1억 개, 어두운 환경(scotopic vision), 명암 감지
- **원추체(Cones)**: 약 650만 개, 밝은 환경(photopic vision), 색 감지
 
> 시험 포인트: "밝은 곳에서의 눈 상태?" → **원추체(Cones)**
 
- **Luminance**: 물리적 밝기 (측정 가능한 값)
- **Brightness**: 사람이 인지하는 밝기
 
> 시험 포인트: "사람이 느끼는 밝기값은?" → **Brightness**
 
- **Simultaneous Contrast**: 같은 밝기도 주변 밝기에 따라 다르게 느껴지는 현상
- **Mach Band**: 밝기 경계에서 실제보다 더 밝거나 어두워 보이는 착시
- **Weber's Law**: ΔI/I = 상수. 밝기 차이 인식 능력은 배경 밝기에 비례
 
---

## 포인트 연산

현재 픽셀 하나의 값만 보고 출력을 결정.

- 음화 변환, 멱함수 변환, 히스토그램 균등화, contrast stretching 

### 음화 변환(Image Negative)

밝은 건 어둡게, 어두운 건 밝게 만듬

>> S = L - 1 - r

r은 입력 픽셀의 현재 밝기값, L은 밝기 레벨의 총 개수(256개), s는 변환 후 출력 밝기값

``` C
void NegativeImage(int** IN, int** OUT, int W, int H)
{
	int i, j;

	// 영상의 모든 픽셀에 대해 반복 수행
	for (j = 0; j < H; j++)              // 세로 방향 (행)
		for (i = 0; i < W; i++)          // 가로 방향 (열)

			// 입력 픽셀 값을 반전하여 출력 영상에 저장
			OUT[j][i] = 255 - IN[j][i];
}
```


### 로그 변환(Log transforamtion)

어두운 부분을 확 펴주고, 밝은 부분은 압축함

>> s = c x log(1 + r)

r이 작을 때(어두울 때) log 곡선이 가파르게 올라가고, r이 클 때(밝을 때) 곡선이 완만해짐

### 멱함수 변환(Power-law transforamtion)

γ(감마)값 하나로 영상을 밝게도, 어둡게도 만들 수 있는 변환.

>> s = cr^γ

γ = 1이면 아무 변화 없음.
γ < 1이면 영상이 밝아짐.
γ > 1이면 영상이 어두워짐.

``` C
void PowerLawTransform(int** IN, int** OUT, int W, int H)
{
	int i, j;
	float gamma;

	// 사용자로부터 감마 값 입력
	printf("\n\t[] Enter Gamma Factor : \t");
	scanf("%f", &gamma);

	// 영상의 모든 픽셀에 대해 감마 변환 수행
	for (j = 0; j < H; j++)              // 세로 방향 반복
		for (i = 0; i < W; i++)          // 가로 방향 반복

			/*
				IN[j][i] / 255. : 입력 값을 0~1 범위로 정규화
				pow(..., gamma) : 감마 값 적용
				255를 곱하여 다시 0~255 범위로 변환
				+0.5는 반올림을 위한 처리
			*/
			OUT[j][i] = Clipping((int)(
				255. * pow(IN[j][i] / 255., gamma) + 0.5
				));
}
```

* 감마 보정 *
- CRT 모니터에서 사용

### 대비 확장(Constrast Stretching)

밝기 범위를 구간별로 쪼개서 각 구간에 다른 기울기를 적용하는 방식
ㄴ 부분 선형 변환이라고도 함
ㄴ 내가 원하는 밝기 구간만 골라서 대비를 키우겠다는 게 가능


>> 구간 1 (0 ≤ r < a): 기울기 α로 변환
>> 구간 2 (a ≤ r < b): 기울기 β로 변환
>> 구간 3 (b ≤ r < L): 기울기 γ로 변환

기울기가 1보다 크면 그 구간의 대비가 늘어나고, 1보다 작으면 줄어든다는 것

- 특수한 경우 2가지
1. Clipping
2. Thresholding


```C
void ContrastStretching(int** IN, int** OUT, int W, int H)
{
	int i, j;
	int a, b;                    // 밝기 구간 경계 값
	float alpha, beta, gamma;   // 각 구간의 기울기

	// 구간 경계 값 입력
	printf("\n\t[] Enter a,b value : \t");
	scanf("%d %d", &a, &b);

	// 각 구간의 기울기 값 입력
	printf("\n\t[] Enter alpha, beta, gamma : \t");
	scanf("%f %f %f", &alpha, &beta, &gamma);

	// 영상의 모든 픽셀에 대해 대비 확장 수행
	for (j = 0; j < H; j++)             // 세로 방향 반복
		for (i = 0; i < W; i++) {       // 가로 방향 반복

			// 1구간: r < a
			// 낮은 밝기 영역에 대한 선형 변환
			if (IN[j][i] < a)
				OUT[j][i] = (int)(alpha * IN[j][i] + 0.5);

			// 2구간: a ≤ r < b
			// 중간 밝기 영역에 대한 선형 변환
			else if (IN[j][i] >= a && IN[j][i] < b)
				OUT[j][i] = (int)(
					beta * (IN[j][i] - a) + alpha * a + 0.5
					);

			// 3구간: r ≥ b
			// 높은 밝기 영역에 대한 선형 변환
			else
				OUT[j][i] = (int)(
					gamma * (IN[j][i] - b)
					+ alpha * a
					+ beta * (b - a)
					+ 0.5
					);
		}
}
```

### 히스토그램 균등화(Histogram Equalization)

- 히스토그램이란?
영상에서 각 밝기값(0~255)을 가진 픽셀이 몇 개인지 세서 막대그래프로 그린 것

- 균등화의 목표?
이 몰려있는 분포를 0~255 전체 범위에 골고루 퍼뜨리는 것

따라서 CDF(누적분포함수)를 이용
ㄴPDF를 -∞부터 x까지 적분한 것


```C
void ComputeHistogram(int** IN, int* histo, int width, int height)
{
	int i, j;

	// 히스토그램 배열 초기화
	for (i = 0; i < 256; i++)
		histo[i] = 0;

	// 각 픽셀 값을 확인하여 해당 밝기 값의 개수 증가
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++) {
			histo[IN[j][i]]++;
		}
}

void DrawHistogram(int* histo, int width, int height)
{
	int** hisimg, i, j, sum, color, max_histo;
	float sumf;
	char name[100];

	// 히스토그램 이미지 메모리 할당
	hisimg = (int**)Imalloc2(256, 256);

	// 이미지 초기화
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
			hisimg[j][i] = 0;

	// 최대 히스토그램 값 찾기 (정규화용)
	for (max_histo = 0, color = 0; color < 256; color++)
		if (histo[color] > max_histo)
			max_histo = histo[color];

	// 막대 그래프 형태로 히스토그램 그리기
	for (color = 0; color < 256; color++)
		for (j = height - histo[color] * height / (3 * max_histo); j < height; j++)
			hisimg[j][color] = 255;

	// 누적 히스토그램(CDF) 곡선 표시
	for (sum = 0, color = 0; color < 256; color++) {
		sum += histo[color];
		sumf = height - (float)sum / (width * height) * height;
		hisimg[Clipping((int)(sumf))][color] =
			(hisimg[Clipping((int)(sumf))][color] == 0) ? 255 : 0;
	}

	// 히스토그램 이미지 저장
	GetFileName(name, "Enter histogram image name : ");
	WriteImage(name, hisimg, 256, 256);

	Ifree2(hisimg, width, height);
}

void HistogramEqualization(int** orgimg, int** outimg, int* histo, int width, int height)
{
	int i, j, color;
	double sumf = 0.;

	// 누적 분포 함수(CDF) 계산 및 매핑 값 생성
	for (color = 0, sumf = 0.; color < 255; color++) {
		sumf += 255. * histo[color] / (width * height);
		histo[color] = (int)(sumf + .5);
	}

	// 변환된 히스토그램 값을 이용하여 출력 영상 생성
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
			outimg[j][i] = histo[orgimg[j][i]];
}
```

### 산술/논리 연산

논리 연산: AND 마스크로 원하는 영역만 추출하거나, OR 마스크로 나머지 영역을 흰색으로 채우는 기법.

산술 연산: 덧셈(밝게), 뺄셈(차영상 = 두 영상의 변화 검출), 곱셈/나눗셈(대비 조절). 특히 영상 평균이 중요한데, 같은 장면의 잡음 낀 영상 K장을 평균하면 잡음 분산이 1/K로 줄어든다는 게 핵심.


## 공간 연산

### 평활화(Smoothing) 필터

주변 픽셀들의 평균을 내서 영상을 부드럽게 만드는 필터. 3×3 box filter는 마스크 안 9개 값을 모두 더해서 9로 나누는 거고, weighted average는 가운데에 가중치를 더 주는 방식.
ㄴ 잡음 제거에 효과적, 부작용으로 에지도 흐려짐, 마스크가 커질수록 블러 심해짐

- 중앙값(Median) 필터
 마스크 안의 값들을 크기 순으로 정렬해서 가운데 값을 출력하는 비선형 필터인데, 임펄스 잡(salt-and-pepper)에 특히 강함

``` C
void SmoothingFilter(int** inimg, int** outimg, int width, int height)
{
	int i, j, dx, dy;
	float** coeff;

	// 필터 크기 입력
	printf("\n\t[] Enter Filter Size (dx & dy) : \t");
	scanf("%d %d", &dx, &dy);

	// 필터 계수 메모리 할당
	coeff = Fmalloc2(dx, dy);

	// 평균 필터 계수 설정 (모든 값 동일)
	for (j = 0; j < dy; j++)
		for (i = 0; i < dx; i++)
			coeff[j][i] = 1. / (dx * dy);

	// 선형 필터 적용
	LinearFilter(inimg, outimg, coeff, dx, dy, width, height);

	// 메모리 해제
	Ffree2(coeff, dx, dy);
}

void LinearFilter(int** inimg, int** outimg, float** coeff, int dx, int dy, int width, int height)
{
	int i, j, x, y, hx, hy;
	float sum;

	// 필터 중심 위치 계산
	hx = (dx - 1) / 2;
	hy = (dy - 1) / 2;

	// 경계 처리를 위해 원본 영상 복사
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
			outimg[j][i] = inimg[j][i];

	// 컨볼루션 연산 수행 (경계 제외)
	for (j = hy; j < height - hy; j++)
		for (i = hx; i < width - hx; i++) {

			// 필터 영역 내 픽셀 값과 계수를 곱하여 합산
			for (sum = 0.0, x = -hx; x <= hx; x++)
				for (y = -hy; y <= hy; y++)
					sum += coeff[y + hy][x + hx] * inimg[j + y][i + x];

			// 결과 값을 출력 영상에 저장 (범위 제한)
			outimg[j][i] = Clipping((int)(sum + 0.5));
		}
}

void MedianFilter(int** inimg, int** outimg, int width, int height)
{
	int i, j, x, y, dx, dy, hx, hy;
	int* array;

	// 필터 크기 입력
	printf("\n\t[] Enter Filter Size (dx & dy) : \t");
	scanf("%d %d", &dx, &dy);

	// 필터 중심 계산
	hx = (dx - 1) / 2;
	hy = (dy - 1) / 2;

	// 필터 영역 값을 저장할 배열 생성
	array = (int*)malloc(sizeof(int) * (dx * dy));

	// 각 픽셀에 대해 중앙값 계산
	for (j = hy; j < height - hy; j++)
		for (i = hx; i < width - hx; i++) {

			// 필터 영역 픽셀 값 복사
			for (y = 0; y < dy; y++)
				for (x = 0; x < dx; x++)
					array[y * dx + x] = inimg[j - hy + y][i - hx + x];

			// 중앙값 계산 후 출력
			outimg[j][i] = GetMedian(array, dx * dy);
		}
}

int GetMedian(int* array, int N)
{
	int top, search, tmp;

	// 내림차순 정렬
	for (top = 0; top < N - 1; top++) {
		for (search = top + 1; search < N; search++) {
			if (array[search] > array[top]) {
				tmp = array[search];
				array[search] = array[top];
				array[top] = tmp;
			}
		}
	}

	// 중앙값 반환
	return(array[N / 2]);
}
```

### 선명화(Sharpening) 필터

평활화가 적분(평균)이면, 선명화는 미분. 2차 미분인 라플라시안을 써서 에지를 강조

``` C
void SharpeningFilter(int** inimg, int** outimg, int width, int height)
{
	int i, j;
	float** coeff;

	// 3x3 필터 계수 생성
	coeff = Fmalloc2(3, 3);

	// 라플라시안 기반 계수 설정
	for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
			coeff[j][i] = -1.;

	coeff[1][1] = 9.;   // 중심 강조

	// 선형 필터 적용
	LinearFilter(inimg, outimg, coeff, 3, 3, width, height);

	// 메모리 해제
	Ffree2(coeff, 3, 3);
}
```
# 노이즈 생성

## 가우시안 잡음(Gaussian Noise)

원래 영상에 랜덤 값을 더하는 방식. g(x,y) = f(x,y) + η(x,y)에서 η가 평균 m, 표준편차 σ인 가우시안 분포를 따르는 잡음

### 가우시안 분포 PDF
 
>> p(x) = (1 / √(2πσ²)) × exp(-(x-m)² / 2σ²)
 
m은 평균, σ는 표준편차.
 
### 생성 방법 — 중심극한정리 이용
 
균일분포 난수를 여러 개 더하면 가우시안 분포에 근사한다는 원리를 이용.
 
**균일분포 난수 12개를 합산하는 방법:**
 
>> η = σ × (Σᵢ₌₁¹² uᵢ - 6) + m
 
- uᵢ: [0, 1] 범위의 균일분포 난수
- 12개를 합산하면 평균 6, 분산 1인 근사 가우시안이 됨
- (합 - 6)으로 평균을 0으로 맞추고, σ를 곱해 원하는 분산으로 조절, m을 더해 평균 이동
 
### 잡음 생성 코드
 
```C
void AddGaussianNoise(int **IN, int **OUT, float mean, float std, int width, int height)
{
    int i, j, k, sum;
 
    for (j = 0; j < height; j++)
        for (i = 0; i < width; i++) {
 
            // 균일분포 난수 12개 합산 → 가우시안 근사 (중심극한정리)
            for (k = 0, sum = 0; k < 12; k++)
                sum += rand();
 
            // 원본 영상에 가우시안 잡음 더하기
            OUT[j][i] = clip(IN[j][i]
                + (int)(std / RAND_MAX * (sum - 6 * RAND_MAX) + mean + 0.5));
        }
}
```

## 임펄스 잡음(Impulse Noise = Salt-and-Pepper Noise)

랜덤 위치의 픽셀을 0(검정 = pepper)이나 255(흰색 = salt)로 바꿔버리는 방식

- 왜 임펄스 잡음에 평활화 필터를 쓰면 안 되는가?
평활화 필터는 극단값(0 또는 255)의 크기를 줄이기는 하지만, 그 잡음 성분이 주위 화소로 번지게 되고 블러링까지 발생한다. 반면 중앙값 필터는 블러링 없이 임펄스 잡음을 깔끔하게 제거할 수 있다.

### 임펄스 잡음 생성 코드
 
```C
void AddSpotNoise(int **IN, int **OUT, float density, int val, int width, int height)
{
    int i, x, y, num, rr;
 
    // 잡음 점의 개수 = 전체 픽셀 × 밀도(%)
    num = (int)(width * height * density);
 
    // 원본 복사
    CopyImage(IN, OUT, width, height);
 
    // 랜덤 위치에 val(0=pepper 또는 255=salt)을 찍음
    for (i = 0; i < num; i++) {
        rr = rand();
        y = (int)((float)rr / RAND_MAX * (height - 1));
        x = rr % width;
        OUT[y][x] = val;
    }
}
```