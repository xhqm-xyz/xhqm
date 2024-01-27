
//#define USING_XHQM
#ifdef USING_XHQM
#define XHQM_METACLASS
#define XHQM_CONCEPTION
#define XHQM_PATTERN
#define XHQM_SYSTEM
#define XHQM_SOFTWARE
#define XHQM_UNIVERSE
#define XHQM_UNIVERSE_INFO
#define XHQM_UNIVERSE_MATH
#define XHQM_UNIVERSE_ALGORITHM
#define XHQM_UNIVERSE_LIFE
#define XHQM_UNIVERSE_SOUL
#define XHQM_UNIVERSE_GAME
#endif

#include "head.h"
#define XHQM_NAMESPACE
#ifdef XHQM_NAMESPACE
using namespace xhqm::templates;
using namespace xhqm::literals;
#endif

#ifdef XHQM_METACLASS
#include "metaclass/template.h"
#include "metaclass/compute.h"
#include "metaclass/object.h"
#include "metaclass/symbols_has.h"
#include "metaclass/class_type.h"
#endif

#ifdef XHQM_CONCEPTION
#include "conception/struct.h"
#include "conception/stacks.h"
#include "conception/queues.h"
#include "conception/plugin.h"
#include "conception/exist.h"
#include "conception/event.h"
#include "conception/element.h"
#include "conception/colors.h"
#endif

#ifdef XHQM_PATTERN
#include "pattern/instance.h"
#include "pattern/observer.h"
#endif

#ifdef XHQM_SYSTEM
#include "system/libmange.h"
#include "system/timesys.h"
#include "system/filesys.h"
#include "system/codesys.h"
#endif

#ifdef XHQM_SOFTWARE
#include "software/mousekey_events.h"
#include "software/signalslot_events.h"
//#include "software/signal.h"
#include "software/command.h"
#include "software/action.h"
#include "software/page.h"
#endif

#ifdef XHQM_UNIVERSE

#endif

#ifdef XHQM_UNIVERSE_INFO
#include "universe/info/infomation.h"
#include "universe/info/fileinfo.h"
#include "universe/info/igesfile.h"
#include "universe/info/stlfile.h"
#include "universe/info/csvfile.h"
#include "universe/info/xcfg.h"
#include "universe/info/xlog.h"
#endif

#ifdef XHQM_UNIVERSE_MATH
#include "universe/math/number.h"
#include "universe/math/point.h"
#include "universe/math/vector.h"
#include "universe/math/matrix.h"
#include "universe/math/gather.h"
#endif

#ifdef XHQM_UNIVERSE_ALGORITHM
#include "universe/math/algorithm/crc.h"
#include "universe/math/algorithm/ransac.h"
#include "universe/math/algorithm/geometry.h"
#include "universe/math/algorithm/analysis.h"
#include "universe/math/algorithm/extremum.h"
#endif

#ifdef XHQM_UNIVERSE_LIFE

#endif

#ifdef XHQM_UNIVERSE_SOUL

#endif

#ifdef XHQM_UNIVERSE_GAME

#endif