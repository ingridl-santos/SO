#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <mutex>
#include <time.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <semaphore.h>
#include <vector>
#include <algorithm>

using namespace std;

#define STOCK_SIZE 5
#define DEFAULT_AMOUNT 40
#define STORES 12 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

time_t rawtime;
struct tm * timeinfo;
static sem_t stock_semaphore;
static mutex stock_mutex;

void time_now() {
  time (&rawtime);
  timeinfo = localtime(&rawtime);
}

struct Product {
  int id;
  int amount;
};

Product stock[STOCK_SIZE];

void initStock() {
  for (int i=0; i < STOCK_SIZE; ++i) {
    stock[i].id = i;
    stock[i].amount = DEFAULT_AMOUNT;
  }
}

void printStock() {
  printf("--------AZEITE STOCK--------\n");
  for (int i=0; i < STOCK_SIZE; ++i) {
    printf("Product [%d]\tAmount: %d\n", stock[i].id, stock[i].amount);
  }
}

struct Thread_Args {
  long thread_id;
  int product_id = -1; // -1 if is not to read
  int quantity;
};

void *reader(void *args) {
  Thread_Args arguments;
  arguments = *(struct Thread_Args*)args;
  
  long thread_id = arguments.thread_id;
  int product_id = arguments.product_id;
  time_now();
  // Thread start
  
  printf("+++ Thread OF READ tid[%ld] invoked!! %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  // sem_wait(&stock_semaphore);

  printf(ANSI_COLOR_GREEN "[SYS][READ]->" ANSI_COLOR_RESET "TID[%ld] starting!!\n\t** ENTERING CRITIC REGION !!** %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  sleep(2);
  
  time_now();
  printf(ANSI_COLOR_YELLOW "[RUNNING][READ]" ANSI_COLOR_RESET "->TID[%ld] %d:%d:%d\n\tReading data from PRODUCT_ID=[%d]. AMOUNT=[%d]\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec, product_id, stock[product_id].amount);

  time_now();
  printf(ANSI_COLOR_RED "[SYS][READ]" ANSI_COLOR_RESET "Thread OF READ tid[%ld] finished!!\n\t** LEFTING  CRITIC REGION !!** %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  
  // sem_post(&stock_semaphore);
  
  pthread_exit(NULL);  
}

void *writer(void *args) {
  srand(time(NULL));
  Thread_Args arguments;
  arguments = *(struct Thread_Args*)args;
  
  long thread_id = arguments.thread_id;
  int product_id = arguments.product_id;
  int quantity = arguments.quantity;
  
  time_now();
  // Thread start
  
  printf("+++ Thread OF WRITE tid[%ld] invoked!! %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  // sem_wait(&stock_semaphore);

  printf(ANSI_COLOR_GREEN "[SYS][WRITE]->" ANSI_COLOR_RESET "TID[%ld] starting!!\n\t** ENTERING CRITIC REGION !!** %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  // sleep((rand() % 3 + 1));
  sleep(4);
  
  time_now();
  printf(ANSI_COLOR_YELLOW "[RUNNING][WRITE]->" ANSI_COLOR_RESET "TID[%ld] %d:%d:%d\n\tWriting data from PRODUCT_ID=[%d]. AMOUNT=[%d] -> [%d]\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec, product_id, stock[product_id].amount, stock[product_id].amount + quantity);
  stock[product_id].amount += quantity;
  
  time_now();
  printf(ANSI_COLOR_RED "[SYS][WRITE]->" ANSI_COLOR_RESET "TID[%ld] finished!!\n\t** LEFTING  CRITIC REGION !!** %d:%d:%d\n", thread_id, timeinfo->tm_hour, timeinfo->tm_hour, timeinfo->tm_sec);
  
  // sem_post(&stock_semaphore);
  
  pthread_exit(NULL);   
}

int main() {
  /* 
    O tema abordado será um estoque de uma distribuidora.
    Cada loja compradora de Product será uma thread.
  */
  srand(time(NULL));
  int stopper_flag;
  int product_target = 1;
  int readers;
  int writers;
  cin >> readers >> writers;
  printf("\nNumber of readers: %d\tNumber of writers: %d\n\n", readers, writers);

  int max_threads = readers + writers;
  pthread_t stores[max_threads];
  int writes_op[writers]; // values of change the amount

  for (int i = 0; i < writers; ++i) {
    cin >> writes_op[i];
    // cout << writes_op[i] << endl;
  }

  vector<int> shuffled_ops;
  for (int i = 0; i < writers; ++i) {
    shuffled_ops.push_back(writes_op[i]);
  }
  for (int i = 0; i < readers; ++i) {
    shuffled_ops.push_back(0);
  }
  random_shuffle ( shuffled_ops.begin(), shuffled_ops.end() );

  // for (int i = 0; i < shuffled_ops.size(); ++i) {
  //   cout << shuffled_ops[i] << " ";
  // }
  // cout << endl;
  initStock();
  printStock();

  printf("\n**** starting main ****\n\n");
  Thread_Args args;

  int tid = 0; // var to control thread id through w and r

  for(int i = 0; i < shuffled_ops.size(); ++i) {
    if (shuffled_ops[i] == 0) {
      args = {
        tid,
        product_target,
      };
      stopper_flag = pthread_create(&stores[tid], NULL, reader, &args);
    } else {
      args = {
        tid,
        product_target,
        shuffled_ops[i], 
      };
      stopper_flag = pthread_create(&stores[tid], NULL, writer, &args);
    }
    if (stopper_flag != 0) {
      cout << "Error creating thread " << tid << ". Return code:" << stopper_flag <<  endl;
    }
    tid++;
    sleep(0.0005);
  }

  for(int i = 0; i < max_threads; i++) {
    pthread_join(stores[i], NULL);
  }
  cout << "All threads completed." << endl;

  printf("\n**** ending main ****\n\n");
  printStock();
  return 0;
}
