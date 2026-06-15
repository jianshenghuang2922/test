#include <fcntl.h>
#include <stdio.h>

void showOp() {
  printf("\n请输入选项: \n");
  printf("1.添加任务\n");
  printf("2.查看任务\n");
  printf("3.删除任务\n");
  printf("4.删除所有任务\n");
  printf("0.退出\n");
  printf("\n");
}
int showTasks() {
  char buffer[255];
  int lineNum = 1;
  FILE *fd = fopen("save.txt", "r");
  if (fd == NULL) {
    printf("\n暂无待办事项\n");
    fclose(fd);
	return 1;
  }
  while (fgets(buffer, sizeof(buffer), fd) != NULL) {
    printf("[%d] %s", lineNum++, buffer);
  }
  if (lineNum == 1) {
	printf("暂无任务\n")
  }
  fclose(fd);
  return 0;
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
      printf("================");
      return 0;
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
      showTasks();
      break;
    }
    case 3: {
	  if (showTasks() == 1) break; 
      printf("--------------\n");
      printf("请输入要删除任务的id: \n");
      int deleteId;
      while (scanf("%d", &deleteId) != 1 || deleteId < 1) {
        printf("请输入有效id\n");
      }
	  getchar();
	  FILE* src = fopen("save.txt", "r");
	  FILE* tmp = fopen("temp.txt", "w");
	  if (tmp == NULL || src == NULL) {
		printf("无法打开或创建临时文件\n");
		fclose(tmp);
		fclose(src);
		break;
	  }
	  char buffer[255];
	  int cur_line = 1;
	  int found = 0;
	  while (fgets(buffer, sizeof(buffer), src) != NULL) {
		if (cur_line == deleteId) {
			found = 1;
		} else {
			fputs(buffer, tmp);
		}
		cur_line += 1;
	  }
	  fclose(src);
	  fclose(tmp);
	  if (found) {
		remove("save.txt");
		rename("temp.txt", "save.txt");
		printf("任务删除成功\n");
	  } else {
		remove("temp.txt");
		printf("未找到id为[%d]的任务\n", deleteId);
	  }
	  break;
    }
    case 4: {
      FILE *fd = fopen("save.txt", "w");
      fclose(fd);
	  printf("任务已全部删除\n");
      break;
    }
    default: {
      printf("未知选项， 请重新输入\n");
    }
    }
  }

  return 0;
}
