#include <stdio.h>
#include <stdlib.h>

#define TESTCASES 33

int main(int argc, char **argv)
{
  int ret = system("make clean && make");
  if (ret == 0) {
    printf("✓ make successful.\n");
  } else {
    printf("✗ make error.\n");
    return 1; // make 실패 시 테스트 진행 X
  }

  char cmd[1024];

  if (argc == 1) { // 모든 테스트 케이스 실행

    for (int i = 1; i <= TESTCASES; i++) {

      // 1) 실행 커맨드 문자열 만들기
      printf("---------------TEST #%d-----------------\n", i);
      sprintf(cmd,
              "./cminus_semantic testsuite/test_%d.cm > testsuite/%d.out",
              i,
              i);
      system(cmd);

      // 2-a) Sort 및 Diff 실행 (diff 결과를 ret에 저장)
      sprintf(
          cmd,
          "sort testsuite/%d.out > testsuite/temp_current_%d.sorted && "
          "sort testsuite/result_%d.txt > testsuite/temp_expect_%d.sorted && "
          "diff testsuite/temp_current_%d.sorted "
          "testsuite/temp_expect_%d.sorted",
          i,
          i,
          i,
          i,
          i,
          i);
      ret = system(cmd);

      // 2-b) 임시 파일 정리 (ret 해석 전에 먼저 실행)
      char cleanup_cmd[256];
      sprintf(cleanup_cmd,
              "rm -f testsuite/temp_current_%d.sorted "
              "testsuite/temp_expect_%d.sorted",
              i,
              i);
      system(cleanup_cmd); // 청소는 diff 결과와 무관하게 실행

      // 2-c) 결과 해석
      if (ret == 0) {
        printf("SUCCESS: test_%d.cm passed.\n", i);
      } else if (ret == 256) { // == (1 << 8), 실제 diff exit 1
        printf("FAIL: test_%d.cm failed.\n", i);
        sprintf(
            cmd,
            "echo expecting: && cat testsuite/result_%d.txt && echo current: "
            "&& cat testsuite/%d.out && cat "
            "testsuite/test_%d.cm",
            i,
            i,
            i);
        system(cmd);
      } else {
        printf("ERROR: diff command failed for test_%d.cm\n", i);
      }
    }

  } else { // 개별 테스트 케이스 실행 (인자 입력 시)

    int i = atoi(argv[1]);

    printf("---------------TEST #%d-----------------\n", i);
    sprintf(
        cmd, "./cminus_semantic testsuite/test_%d.cm > testsuite/%d.out", i, i);
    system(cmd);

    // Sort 및 Diff 실행
    sprintf(
        cmd,
        "sort testsuite/%d.out > testsuite/temp_current_%d.sorted && "
        "sort testsuite/result_%d.txt > testsuite/temp_expect_%d.sorted && "
        "diff testsuite/temp_current_%d.sorted testsuite/temp_expect_%d.sorted",
        i,
        i,
        i,
        i,
        i,
        i);
    ret = system(cmd);

    // 임시 파일 정리
    char cleanup_cmd[256];
    sprintf(cleanup_cmd,
            "rm -f testsuite/temp_current_%d.sorted "
            "testsuite/temp_expect_%d.sorted",
            i,
            i);
    system(cleanup_cmd);

    // 결과 해석
    if (ret == 0) {
      printf("SUCCESS: test_%d.cm passed.\n", i);
    } else if (ret == 256) { // == (1 << 8), 실제 diff exit 1
      printf("FAIL: test_%d.cm failed.\n", i);
      sprintf(cmd,
              "echo expecting: && cat testsuite/result_%d.txt && echo current: "
              "&& cat testsuite/%d.out && cat "
              "testsuite/test_%d.cm",
              i,
              i,
              i);
      system(cmd);
    } else {
      printf("ERROR: diff command failed for test_%d.cm\n", i);
    }
  }

  return 0;
}
