# Chapter3_HW7
내일배움캠프 Chapter3 과제7번 제출용 저장소

[채점 자가진단 (블로그 글, 클릭시 이동)](https://15danpancake.atlassian.net/wiki/spaces/cdg1212/pages/69566629/Chapter+3+7+Pawn+3D#%EC%B1%84%EC%A0%90-%EC%9E%90%EA%B0%80%EC%A7%84%EB%8B%A8)


## Environment

개발은 Windows x86에서 이루어졌으며, 사용한 Unreal Engine 버전은 5.5.4 입니다.


## Youtube
[![ALTTEXT](https://img.youtube.com/vi/AAAAAAAAAAAAAAAAAAAAA/0.jpg)](https://www.youtube.com/watch?v=AAAAAAAAAAAAAAAAAAAAA)

- ...


## TestMap 설명

TestMap을 시작하면, 다음과 같은 모습을 볼 수 있습니다.  
![image](https://github.com/user-attachments/assets/249ac567-8d65-4bab-9818-3d6a1d553971)


각 흰색 발판에 올라가면, Movement 속성을 즉시 변경할 수 있습니다. 예를 들어, 아래 발판을 밟으면 중력 가속도가 변합니다.  
![image](https://github.com/user-attachments/assets/0025ac41-5470-4ad2-9679-dee9edbd2220)


변경된 값은 앞에 있는 벽의 텍스트를 통해 확인할 수 있습니다.  
![image](https://github.com/user-attachments/assets/0f8bef00-ea4f-4880-b4b6-37b1ee833c1b)


다양한 장애물이 있으니, 직접 캐릭터를 움직여 올바르게 움직이는지 테스트할 수 있습니다.  
![image](https://github.com/user-attachments/assets/2f6dd796-27b1-4388-b631-da66567b6c4e)

![image](https://github.com/user-attachments/assets/14a9127d-3470-45ed-964b-002451daf1a6)


맵 변경 발판을 이용하면, 맵을 변경할 수 있습니다.  
![image](https://github.com/user-attachments/assets/ca9d4594-0b38-4df7-8e2e-071e9fa14f7e)


## Files

### Contents
- Content/Homework_7
  * Blueprints/
    - 각종 블루프린트. 폰, 플레이어컨트롤러, 게임모드베이스...
    - TestButton/, TestText/
      * 테스트용 Actors (버튼과 텍스트)
  * Maps/
    - TestMap (메인 맵)
    - DroneMap
  * Inputs/
    - Character/
      * IMC_Character
      * IA_Jump, IA_Look, IA_Move, IA_Sprint, IA_ToggleCamera, IA_ZoomCamera
    - Drone/
      * IMC_Drone
      * IA_Fly, IA_Land, IA_Move, IA_Rotate
  * Character/
    - 캐릭터 관련 컨텐츠
    - 스켈레톤, 스켈레탈메시, 피직스에셋, 머티리얼, 텍스처, 애니메이션이 포함되어 있음

### Source Codes

- Source/Homework_7/Public/
  * Movement 관련
    - MyPhysicsMovement.h
      * 기본 힘 기반 물리 시뮬레이션 클래스
    - MyCharacterMovement.h
    - MyDroneMovement.h
  * Pawn 관련
    - 실제로 움직일 Pawn 하위 클래스. 각각 캐릭터와 드론을 나타냄
    - MyPawn.h
    - MyDrone.h
  * Controller 관련
    - IMC 및 IA 처리
    - MyPlayerController.h
    - MyDroneController.h
