#ifndef log_warper_h__
#define log_warper_h__

#include <muradin/config/known_env.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h> // for strrchr strerror

#if (defined( _ENV_WIN))
#include <Windows.h> // for GetLastError
#define		get_last_error_		(::GetLastError())
#else
#include <errno.h>
#define		get_last_error_		(errno)
#endif 

namespace muradin
{
namespace base{

class	loger;

enum	loging_level{
	ll_debug,
	ll_info,
	ll_warning,
	ll_error,
	ll_fatal_err,
	ll_end_palce_
};

typedef void (*OutputFunc)(const char* msg, int len);
typedef void (*FlushFunc)();



class log_warper
{
public:
	explicit	log_warper(loging_level log_lvl);
	log_warper(loging_level log_lvl,const std::string& source_file,const std::string& func_name,int line_number);
	log_warper(loging_level log_lvl,const std::string& source_file,const std::string& func_name,int line_number,int error_code);
	std::ostream&	stream();
	void		finish();
	void		flush();
	loger&		get_impl();
	~log_warper(void);

	static loging_level logLevel();
	static void setLogLevel(loging_level level);

	static void setOutput(OutputFunc func);
	static void setFlush(FlushFunc func);
private:
	log_warper(const log_warper&);
	log_warper&	operator=(const log_warper&);
private:
	loger*		impl_;
};

};//base
};//muradin

#define		debug_loger					(muradin::base::log_warper(muradin::base::ll_debug,__FILE__,__FUNCTION__,__LINE__))
#define		debug_err_loger				(muradin::base::log_warper(muradin::base::ll_debug,__FILE__,__FUNCTION__,__LINE__,(get_last_error_)))
#define		info_loger					(muradin::base::log_warper(muradin::base::ll_info,__FILE__,__FUNCTION__,__LINE__))
#define		warn_loger					(muradin::base::log_warper(muradin::base::ll_warning,__FILE__,__FUNCTION__,__LINE__))
#define		err_loger					(muradin::base::log_warper(muradin::base::ll_error,__FILE__,__FUNCTION__,__LINE__))
// write log and call abort()
#define		fata_loger					(muradin::base::log_warper(muradin::base::ll_fatal_err,__FILE__,__FUNCTION__,__LINE__))

/// end of line
static const char* EOL()
{
#if (defined( _ENV_WIN))
    return "\r\n";
#else
    return "\n";
#endif
}


#endif // log_warper_h__
