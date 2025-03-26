import cv2
import serial
from deepface import DeepFace
from time import sleep

# 시리얼 포트 설정 (아두이노 연결된 포트와 일치해야 함)
ser = serial.Serial('COM9', 9600)  # 아두이노의 포트와 동일하게 설정 (예: COM3, /dev/ttyUSB0 등)

# 비디오 캡처 설정
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # DeepFace를 사용한 표정 감지
    result = DeepFace.analyze(frame, actions=['emotion'], enforce_detection=False)
    
    # 결과에서 감정 추출
    emotion = result[0]['dominant_emotion']

    # 감정에 따라 아두이노로 전송할 값을 설정
    if emotion == "neutral":
        emotion_to_send = "nature"
    elif emotion == "happy":
        emotion_to_send = "happy"
    elif emotion == "sad":
        emotion_to_send = "sad"
    else:
        emotion_to_send = "nature"  # 기본값은 neutral

    # 감정 값을 아두이노로 전송 (시리얼 포트로 전송)
    ser.write(emotion_to_send.encode())
    sleep(1)

    # 얼굴에 감정 표시
    cv2.putText(frame, f'Emotion: {emotion}', (30, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # 결과 화면 출력
    cv2.imshow("Emotion Recognition", frame)

    # 'q' 키를 눌러 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
