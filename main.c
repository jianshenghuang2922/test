#include <fcntl.h>
#include <stdio.h>

void showOp() {
  printf("\n请输入选项: \n");
  printf("1.添加任务\n");
  printf("2.查看任务\n");
  printf("0.退出\n");
  printf("\n");
}

int main(int argc, char **argv) {
  printf("===我的待办事项===\n");

  int op;
  for (;;) {
    
    showOp();
    if (scanf("%d", &op) != 1) {
      printf("请输入有效数字\n");
      while (getchar() != '\n')
        ;
      continue;
    }
    getchar();
    switch (op) {
    case 0: {
      printf("退出成功\n");
      printf("================"); return 0;
    }
    case 1: {
      printf("请输入要添加的任务: \n");
      char description[64];
      fgets(description, sizeof(description), stdin);
      FILE *fd = fopen("save.txt", "a");
      if (fd == NULL) {
        printf("无法打开或创建文件\n");
        return 1;
      }
      fputs(description, fd);
      printf("添加成功\n");
      fclose(fd);
      break;
    }
    case 2: {
      char buffer[255];
      FILE *fd = fopen("save.txt", "r");
      if (fd == NULL) {
        printf("\n暂无待办事项\n");
      }
      while (fgets(buffer, sizeof(buffer), fd) != NULL) {
        printf("%s", buffer);
      }
      fclose(fd);
	  break;
    }
	default: {
		printf("未知选项， 请重新输入\n");
	}
    }
  }

  return 0;
}
