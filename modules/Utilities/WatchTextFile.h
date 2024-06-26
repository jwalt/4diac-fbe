#ifdef FBT_INCLUDES
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <optional>
#else

uint64_t mTimestamp;
char mData[257];

std::optional<TEventID> executeREQ()
{
  var_CHANGED = CIEC_BOOL(false);
  struct stat st;
  int fd = -1;

  do {
    auto fname = var_FILE.getValue();
    if (stat(fname, &st) < 0) break;

    if (st.st_mtime == time_t(mTimestamp)) return scmEventCNFID;
    mTimestamp = uint64_t(st.st_mtime);

    fd = open(fname, O_RDONLY|O_CLOEXEC);
    if (fd < 0) break;

    // read the last N bytes to get the last line
    if (size_t(st.st_size) >= sizeof(mData)
        && lseek(fd, off_t(-sizeof(mData)+1), SEEK_END) < 0) break;

    ssize_t len = read(fd, mData, sizeof(mData)-1);
    if (len < 0) break;

    close(fd);
    fd = -1;

    // only pass on a complete line (prevent partial results)
    if (len == 0 || mData[len-1] != '\n') return scmEventCNFID;
    mData[len] = 0;

    // search for line start
    const char *start = &mData[len];
    while (len-- > 0 && mData[len] != '\n') start--;
    var_CONTENT = CIEC_WSTRING(start);
    var_CHANGED = CIEC_BOOL(true);

    var_STATUS = CIEC_WSTRING("OK");
    return scmEventCNFID;
  } while (false);

  var_STATUS = CIEC_WSTRING(strerror(errno));
  if (fd > 0) close(fd);
  return scmEventCNFID;
}

#endif
