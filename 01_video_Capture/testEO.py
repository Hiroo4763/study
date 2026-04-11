import cv2
import os


# Q ZONE : qqㅂㅂㅂㅂㅂㅂㅂㅂㅂㅂㅂㅂㅂ

test_name = "20260117-오전-뮤지엄B"
# test_name='test1'

# EO_video_path = f'C:/workspace/ETRI_Dataset/2025/{test_name}/1_videos/EO/'
# IR_video_path = f'C:/workspace/ETRI_Dataset/2025/{test_name}/1_videos/IR/'

# EO_image_path = f'C:/workspace/ETRI_Dataset/2025/{test_name}/0_images/EO/'
# IR_image_path = f'C:/workspace/ETRI_Dataset/2025/{test_name}/0_images/IR/'
EO_video_path = f"C:/workspace/ETRI_Dataset/2025/{test_name}/1_videos/IR/"
# IR_video_path = f"C:/workspace/ETRI_Dataset/2025/{test_name}/1_videos/EO/"


EO_image_path = f"C:/workspace/ETRI_Dataset/2025/{test_name}/0_images/IR/"
# IR_image_path = f"C:/workspace/ETRI_Dataset/2025/{test_name}/0_images/EO/"
try:
    os.makedirs(EO_video_path)
    # os.makedirs(IR_video_path)
    print(f"{test_name}의 폴더가 만들어졌습니다.")
except:
    print("이미 폴더가 있습니다.")
try:
    os.makedirs(EO_image_path)
    # os.makedirs(IR_image_path)
    print(f"{test_name}의 폴더가 만들어졌습니다.")
except:
    print("이미 폴더가 있습니다.")

# 비디오 캡처 객체 생성
cap1 = cv2.VideoCapture(1, cv2.CAP_DSHOW)  # 1 : EO
# cap2 = cv2.VideoCapture(2, cv2.CAP_DSHOW)  # 2 : IR
# cap1.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*"MJPG"))
cap1.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)  # 기본 창 설정 1280x720
cap1.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
# cap1.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0.25)
# cap1.set(cv2.CAP_PROP_EXPOSURE, -6)

# cap2.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
# cap2.set(cv2.CAP_PROP_FRAME_HEIGHT, 512)

# fourcc = int(cap1.get(cv2.CAP_PROP_FOURCC))
# print("EO FOURCC:", "".join([chr((fourcc >> 8 * i) & 0xFF) for i in range(4)]))
# print("EO size:", cap1.get(3), cap1.get(4))

# # 비디오 코덱 설정 (여기서는 XVID 사용)
fourcc = cv2.VideoWriter_fourcc(*"XVID")

# 비디오 파일 이름 및 설정
try:
    test_num = (
        max([int(i.lstrip("output").rstrip(".mp4")) for i in os.listdir(EO_video_path)])
        + 1
    )
except:
    test_num = 0

try:
    capNum = (
        max(
            [
                int(i.lstrip("EO_captured").rstrip(".png"))
                for i in os.listdir(EO_image_path)
            ]
        )
        + 1
    )
except:
    capNum = 0

out1 = cv2.VideoWriter(
    os.path.join(EO_video_path, f"output{test_num}.mp4"),
    fourcc,
    20.0,
    (int(cap1.get(3)), int(cap1.get(4))),
)
# out2 = cv2.VideoWriter(
#     os.path.join(IR_video_path, f"output{test_num}.mp4"),
#     # fourcc,
#     20.0,
#     (int(cap2.get(3)), int(cap2.get(4))),
# )

print("비디오 녹화를 시작합니다...")

while True:
    # 카메라에서 프레임 읽기
    ret1, frame1 = cap1.read()
    # ret2, frame2 = cap2.read()

    if ret1:
        m = frame1.mean()
        if m < 2:
            print("EO nearly black, mean:", m)
    if not ret1:
        print("1 카메라에서 프레임을 읽을 수 없습니다.")
        break
    # if not ret2:
    #     print("2 카메라에서 프레임을 읽을 수 없습니다.")
    #     break

    # 프레임을 비디오 파일에 기록
    out1.write(frame1)
    # out2.write(frame2)

    # 프레임을 화면에 표시
    cv2.imshow("Frame", frame1)
    # cv2.imshow("Frame2", frame2)

    if cv2.waitKey(1) & 0xFF == ord("c"):
        print("captured EO/IR frame%04d" % capNum)
        img_captured_1 = cv2.imwrite(
            os.path.join(EO_image_path, "EO_captured%04d.png" % capNum), frame1
        )
        # img_captured_2 = cv2.imwrite(
        #     os.path.join(IR_image_path, "IR_captured%04d.png" % capNum), frame2
        # )
        capNum += 1
    if cv2.waitKey(1) & 0xFF == ord("q"):
        print("done")
        break


# 모든 객체 해제
cap1.release()
# cap2.release()
out1.release()
# out2.release()
cv2.destroyAllWindows()

print("비디오 녹화가 완료되었습니다.")
