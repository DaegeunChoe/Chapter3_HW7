# Chapter3_HW7
내일배움캠프 Chapter3 과제7번 제출용 저장소

[채점 자가진단 (블로그 글, 클릭시 이동)](https://15danpancake.atlassian.net/wiki/spaces/cdg1212/pages/69566629/Chapter+3+7+Pawn+3D#%EC%B1%84%EC%A0%90-%EC%9E%90%EA%B0%80%EC%A7%84%EB%8B%A8)


## Youtube
[![ALTTEXT](https://img.youtube.com/vi/AAAAAAAAAAAAAAAAAAAAA/0.jpg)](https://www.youtube.com/watch?v=AAAAAAAAAAAAAAAAAAAAA)

- ...

## 컨텐츠 
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

## 소스 코드 

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
