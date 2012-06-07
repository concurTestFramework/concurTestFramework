typedef unsigned long size_t;
typedef int wchar_t;
typedef struct suds_type_71 {
  int quot;
  int rem;
} div_t;
typedef struct suds_type_72 {
  long quot;
  long rem;
} ldiv_t;
extern size_t __ctype_get_mb_cur_max() __attribute__ ((__nothrow__));
extern double atof(const char *__nptr) __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern int atoi(const char *__nptr) __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern long atol(const char *__nptr) __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern long long atoll(const char *__nptr) __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern double strtod(const char *__nptr, char **__endptr) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long strtol(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long strtoul(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long long strtoq(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long long strtouq(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long long strtoll(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long long strtoull(const char *__nptr, char **__endptr, int __base) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern double __strtod_internal(const char *__nptr, char **__endptr, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern float __strtof_internal(const char *__nptr, char **__endptr, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long double __strtold_internal(const char *__nptr, char **__endptr, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long __strtol_internal(const char *__nptr, char **__endptr, int __base, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long __strtoul_internal(const char *__nptr, char **__endptr, int __base, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long long __strtoll_internal(const char *__nptr, char **__endptr, int __base, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long long __strtoull_internal(const char *__nptr, char **__endptr, int __base, int __group) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern char *l64a(long __n) __attribute__ ((__nothrow__));
extern long a64l(const char *__s) __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long __int64_t;
typedef unsigned long __uint64_t;
typedef long __quad_t;
typedef unsigned long __u_quad_t;
typedef unsigned long __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long __ino_t;
typedef unsigned long __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long __nlink_t;
typedef long __off_t;
typedef long __off64_t;
typedef int __pid_t;
typedef struct suds_type_73 {
  int __val[2];
} __fsid_t;
typedef long __clock_t;
typedef unsigned long __rlim_t;
typedef unsigned long __rlim64_t;
typedef unsigned int __id_t;
typedef long __time_t;
typedef unsigned int __useconds_t;
typedef long __suseconds_t;
typedef int __daddr_t;
typedef long __swblk_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void *__timer_t;
typedef long __blksize_t;
typedef long __blkcnt_t;
typedef long __blkcnt64_t;
typedef unsigned long __fsblkcnt_t;
typedef unsigned long __fsblkcnt64_t;
typedef unsigned long __fsfilcnt_t;
typedef unsigned long __fsfilcnt64_t;
typedef long __ssize_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long __intptr_t;
typedef unsigned int __socklen_t;
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
typedef int __sig_atomic_t;
typedef struct suds_type_74 {
  unsigned long __val[1024 / (8 * sizeof(unsigned long ))];
} __sigset_t;
typedef __sigset_t sigset_t;
struct timespec {
  __time_t tv_sec;
  long tv_nsec;
} ;
struct timeval {
  __time_t tv_sec;
  __suseconds_t tv_usec;
} ;
typedef __suseconds_t suseconds_t;
typedef long __fd_mask;
typedef struct suds_type_75 {
  __fd_mask __fds_bits[1024 / (8 * sizeof(__fd_mask ))];
} fd_set;
typedef __fd_mask fd_mask;
extern int select(int __nfds, fd_set *__readfds, fd_set *__writefds, fd_set *__exceptfds, struct timeval *__timeout);
extern int pselect(int __nfds, fd_set *__readfds, fd_set *__writefds, fd_set *__exceptfds, struct timespec *__timeout, const __sigset_t *__sigmask);
extern __inline unsigned int gnu_dev_major(unsigned long long __dev) __attribute__ ((__nothrow__));
extern __inline unsigned int gnu_dev_minor(unsigned long long __dev) __attribute__ ((__nothrow__));
extern __inline unsigned long long gnu_dev_makedev(unsigned int __major, unsigned int __minor) __attribute__ ((__nothrow__));
extern __inline unsigned int gnu_dev_major(unsigned long long __dev)
{
  unsigned long long T_66;
  unsigned long long T_67;
  unsigned long long T_68;
  unsigned int T_69;
  int T_70;
  unsigned int T_71;
  unsigned long long T_72;

  T_66 = __dev >> 8;
  T_67 = T_66 & 0xfff;
  T_68 = __dev >> 32;
  T_69 = (unsigned int ) (T_68);
  T_70 = ~0xfff;
  T_71 = T_69 & T_70;
  T_72 = T_67 | T_71;
  return T_72;
}


extern __inline unsigned int gnu_dev_minor(unsigned long long __dev)
{
  unsigned long long T_73;
  unsigned long long T_74;
  unsigned int T_75;
  int T_76;
  unsigned int T_77;
  unsigned long long T_78;

  T_73 = __dev & 0xff;
  T_74 = __dev >> 12;
  T_75 = (unsigned int ) (T_74);
  T_76 = ~0xff;
  T_77 = T_75 & T_76;
  T_78 = T_73 | T_77;
  return T_78;
}


extern __inline unsigned long long gnu_dev_makedev(unsigned int __major, unsigned int __minor)
{
  unsigned int T_79;
  unsigned int T_80;
  unsigned int T_81;
  unsigned int T_82;
  int T_83;
  unsigned int T_84;
  unsigned long long T_85;
  unsigned long long T_86;
  unsigned long long T_87;
  int T_88;
  unsigned int T_89;
  unsigned long long T_90;
  unsigned long long T_91;
  unsigned long long T_92;

  T_79 = __minor & 0xff;
  T_80 = __major & 0xfff;
  T_81 = T_80 << 8;
  T_82 = T_79 | T_81;
  T_83 = ~0xff;
  T_84 = __minor & T_83;
  T_85 = (unsigned long long ) (T_84);
  T_86 = T_85 << 12;
  T_87 = T_82 | T_86;
  T_88 = ~0xfff;
  T_89 = __major & T_88;
  T_90 = (unsigned long long ) (T_89);
  T_91 = T_90 << 32;
  T_92 = T_87 | T_91;
  return T_92;
}


typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef unsigned long pthread_t;
typedef union suds_type_76 {
  char __size[56];
  long __align;
} pthread_attr_t;
typedef struct __pthread_internal_list {
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union suds_type_77 {
  struct __pthread_mutex_s {
    int __lock;
    unsigned int __count;
    int __owner;
    unsigned int __nusers;
    int __kind;
    int __spins;
    __pthread_list_t __list;
  } __data;
  char __size[40];
  long __align;
} pthread_mutex_t;
typedef union suds_type_78 {
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union suds_type_79 {
  struct suds_type_80 {
    int __lock;
    unsigned int __futex;
    unsigned long long __total_seq;
    unsigned long long __wakeup_seq;
    unsigned long long __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  long long __align;
} pthread_cond_t;
typedef union suds_type_81 {
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union suds_type_82 {
  struct suds_type_83 {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long __pad1;
    unsigned long __pad2;
    unsigned int __flags;
  } __data;
  char __size[56];
  long __align;
} pthread_rwlock_t;
typedef union suds_type_84 {
  char __size[8];
  long __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union suds_type_85 {
  char __size[32];
  long __align;
} pthread_barrier_t;
typedef union suds_type_86 {
  char __size[4];
  int __align;
} pthread_barrierattr_t;
extern long random() __attribute__ ((__nothrow__));
extern void srandom(unsigned int __seed) __attribute__ ((__nothrow__));
extern char *initstate(unsigned int __seed, char *__statebuf, size_t __statelen) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate(char *__statebuf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
struct random_data {
  int32_t *fptr;
  int32_t *rptr;
  int32_t *state;
  int rand_type;
  int rand_deg;
  int rand_sep;
  int32_t *end_ptr;
} ;
extern int random_r(struct random_data *__buf, int32_t *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r(unsigned int __seed, struct random_data *__buf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
extern int initstate_r(unsigned int __seed, char *__statebuf, size_t __statelen, struct random_data *__buf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r(char *__statebuf, struct random_data *__buf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int rand() __attribute__ ((__nothrow__));
extern void srand(unsigned int __seed) __attribute__ ((__nothrow__));
extern int rand_r(unsigned int *__seed) __attribute__ ((__nothrow__));
extern double drand48() __attribute__ ((__nothrow__));
extern double erand48(unsigned short __xsubi[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long lrand48() __attribute__ ((__nothrow__));
extern long nrand48(unsigned short __xsubi[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern long mrand48() __attribute__ ((__nothrow__));
extern long jrand48(unsigned short __xsubi[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void srand48(long __seedval) __attribute__ ((__nothrow__));
extern unsigned short *seed48(unsigned short __seed16v[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48(unsigned short __param[7]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
struct drand48_data {
  unsigned short __x[3];
  unsigned short __old_x[3];
  unsigned short __c;
  unsigned short __init;
  unsigned long long __a;
} ;
extern int drand48_r(struct drand48_data *__buffer, double *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r(unsigned short __xsubi[3], struct drand48_data *__buffer, double *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r(struct drand48_data *__buffer, long *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r(unsigned short __xsubi[3], struct drand48_data *__buffer, long *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r(struct drand48_data *__buffer, long *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r(unsigned short __xsubi[3], struct drand48_data *__buffer, long *__result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r(long __seedval, struct drand48_data *__buffer) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
extern int seed48_r(unsigned short __seed16v[3], struct drand48_data *__buffer) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r(unsigned short __param[7], struct drand48_data *__buffer) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *malloc(size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__));
extern void *calloc(size_t __nmemb, size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__));
extern void *realloc(void *__ptr, size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));
extern void free(void *__ptr) __attribute__ ((__nothrow__));
extern void cfree(void *__ptr) __attribute__ ((__nothrow__));
extern void *alloca(size_t __size) __attribute__ ((__nothrow__));
extern void *valloc(size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__));
extern int posix_memalign(void **__memptr, size_t __alignment, size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void abort() __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
extern int atexit(void (*__func)()) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int on_exit(void (*__func)(int __status, void *__arg), void *__arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void exit(int __status) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
extern char *getenv(const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern char *__secure_getenv(const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int putenv(char *__string) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int setenv(const char *__name, const char *__value, int __replace) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv(const char *__name) __attribute__ ((__nothrow__));
extern int clearenv() __attribute__ ((__nothrow__));
extern char *mktemp(char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp(char *__template) __attribute__ ((__nonnull__ (1)));
extern char *mkdtemp(char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int system(const char *__command);
extern char *realpath(const char *__name, char *__resolved) __attribute__ ((__nothrow__));
typedef int (*__compar_fn_t)(const void *, const void *);
extern void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 2, 5)));
extern void qsort(void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern int abs(int __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern long labs(long __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern div_t div(int __numer, int __denom) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern ldiv_t ldiv(long __numer, long __denom) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern char *ecvt(double __value, int __ndigit, int *__decpt, int *__sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
extern char *fcvt(double __value, int __ndigit, int *__decpt, int *__sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
extern char *gcvt(double __value, int __ndigit, char *__buf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3)));
extern char *qecvt(long double __value, int __ndigit, int *__decpt, int *__sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
extern char *qfcvt(long double __value, int __ndigit, int *__decpt, int *__sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
extern char *qgcvt(long double __value, int __ndigit, char *__buf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3)));
extern int ecvt_r(double __value, int __ndigit, int *__decpt, int *__sign, char *__buf, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r(double __value, int __ndigit, int *__decpt, int *__sign, char *__buf, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qecvt_r(long double __value, int __ndigit, int *__decpt, int *__sign, char *__buf, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r(long double __value, int __ndigit, int *__decpt, int *__sign, char *__buf, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int mblen(const char *__s, size_t __n) __attribute__ ((__nothrow__));
extern int mbtowc(wchar_t *__pwc, const char *__s, size_t __n) __attribute__ ((__nothrow__));
extern int wctomb(char *__s, wchar_t __wchar) __attribute__ ((__nothrow__));
extern size_t mbstowcs(wchar_t *__pwcs, const char *__s, size_t __n) __attribute__ ((__nothrow__));
extern size_t wcstombs(char *__s, const wchar_t *__pwcs, size_t __n) __attribute__ ((__nothrow__));
extern int rpmatch(const char *__response) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int posix_openpt(int __oflag);
extern int getloadavg(double __loadavg[], int __nelem) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
typedef __clock_t clock_t;
struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long tm_gmtoff;
  const char *tm_zone;
} ;
struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
} ;
struct sigevent ;
extern clock_t clock() __attribute__ ((__nothrow__));
extern time_t time(time_t *__timer) __attribute__ ((__nothrow__));
extern double difftime(time_t __time1, time_t __time0) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern time_t mktime(struct tm *__tp) __attribute__ ((__nothrow__));
extern size_t strftime(char *__s, size_t __maxsize, const char *__format, struct tm *__tp) __attribute__ ((__nothrow__));
extern struct tm *gmtime(const time_t *__timer) __attribute__ ((__nothrow__));
extern struct tm *localtime(const time_t *__timer) __attribute__ ((__nothrow__));
extern struct tm *gmtime_r(const time_t *__timer, struct tm *__tp) __attribute__ ((__nothrow__));
extern struct tm *localtime_r(const time_t *__timer, struct tm *__tp) __attribute__ ((__nothrow__));
extern char *asctime(struct tm *__tp) __attribute__ ((__nothrow__));
extern char *ctime(const time_t *__timer) __attribute__ ((__nothrow__));
extern char *asctime_r(struct tm *__tp, char *__buf) __attribute__ ((__nothrow__));
extern char *ctime_r(const time_t *__timer, char *__buf) __attribute__ ((__nothrow__));
extern char *__tzname[2];
extern int __daylight;
extern long __timezone;
extern char *tzname[2];
extern void tzset() __attribute__ ((__nothrow__));
extern int daylight;
extern long timezone;
extern int stime(const time_t *__when) __attribute__ ((__nothrow__));
extern time_t timegm(struct tm *__tp) __attribute__ ((__nothrow__));
extern time_t timelocal(struct tm *__tp) __attribute__ ((__nothrow__));
extern int dysize(int __year) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
extern int nanosleep(struct timespec *__requested_time, struct timespec *__remaining);
extern int clock_getres(clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__));
extern int clock_gettime(clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__));
extern int clock_settime(clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__));
extern int clock_nanosleep(clockid_t __clock_id, int __flags, struct timespec *__req, struct timespec *__rem);
extern int clock_getcpuclockid(pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__));
extern int timer_create(clockid_t __clock_id, struct sigevent *__evp, timer_t *__timerid) __attribute__ ((__nothrow__));
extern int timer_delete(timer_t __timerid) __attribute__ ((__nothrow__));
extern int timer_settime(timer_t __timerid, int __flags, struct itimerspec *__value, struct itimerspec *__ovalue) __attribute__ ((__nothrow__));
extern int timer_gettime(timer_t __timerid, struct itimerspec *__value) __attribute__ ((__nothrow__));
extern int timer_getoverrun(timer_t __timerid) __attribute__ ((__nothrow__));
void rand_sleep()
{
  struct timespec time_struct;
  int sleep_time;
  long T_93;
  long T_94;

  T_93 = random();

  T_94 = T_93 % 1000;
  sleep_time = T_94 + 1;
  time_struct.tv_sec = 0;
  time_struct.tv_nsec = sleep_time * 1000000;
  nanosleep(&time_struct,(void *) (0));

}


int getRandom(int seed)
{
  int T_95;
  int T_96;

  srand(seed);

  T_95 = rand();

  T_96 = T_95 % 1001;
  return T_96;
}


int getSeed()
{
  int seed;

  seed = time((void *) (0));

  return seed;
}



