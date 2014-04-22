// C-Standard
#include <cstring>
// STL
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
// Boost
#include <boost/date_time/posix_time/posix_time.hpp>
// FastCGI++
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>
// Sqlite3
#include <sqlite3.h>

int g_id = -1;

void error_log(const char* msg) {
    using namespace std;
    using namespace boost;
    static ofstream error;
    if(!error.is_open()) {
        error.open("/tmp/errlog", ios_base::out | ios_base::app);
        error.imbue(locale(error.getloc(), new posix_time::time_facet()));
    }//if
    error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}

static int db_callback_select_id(void * NotUsed, int argc, char ** argv, char ** azColName) {
    (void)(NotUsed);
    (void)(azColName);

    if(argc != 1) {
        const char * errmsg = "SELECT FROM idTable with data size greater than 1";
        error_log(errmsg);
        throw std::runtime_error(errmsg);
    }//if

    g_id = atoi(argv[0]);

    return 0;
}//db_callback_select_id(NotUsed, argc, argv, azColName)

static int db_callback_insert(void * NotUsed, int argc, char ** argv, char ** azColName) { return 0; }

static int db_callback_update_id(void * NotUsed, int argc, char ** argv, char ** azColName) { return 0; }

static void
updateFormData(std::vector<std::string> & formdata, const std::wstring & key, const std::wstring & value) {
    static bool keymap_init = false;
    static std::map<std::string, int> keymap;
    if(keymap_init == false) {
        keymap.insert(std::make_pair("id", 0));
        keymap.insert(std::make_pair("name", 1));
        keymap.insert(std::make_pair("email", 2));
        keymap.insert(std::make_pair("gender", 3));
        keymap.insert(std::make_pair("hobby-football", 4));
        keymap.insert(std::make_pair("hobby-music", 5));
        keymap.insert(std::make_pair("hobby-dancing", 6));
        keymap.insert(std::make_pair("hobby-comics", 7));
        keymap.insert(std::make_pair("messageArea", 8));
        keymap.insert(std::make_pair("submit", -1));
        keymap.insert(std::make_pair("reset", -1));
        keymap_init = true;
    }//if

    const std::string keystr = std::string(key.begin(), key.end());
    std::map<std::string, int>::iterator finditer = keymap.find(keystr);
    if(finditer != keymap.end()) {
        int idx = finditer->second;
        if(idx < 0)
            return;

        if(idx >= 4 && idx <= 7) {
            formdata[idx] = "1";
        } else {
            formdata[idx] = std::string(value.begin(), value.end());
        }//if-else
    } else {
        std::string errstr = "invalid key string: " + keystr;
        error_log(errstr.c_str());
        throw std::runtime_error(errstr.c_str());
    }//if-else
}//updateFormData(formdata, key, value)

class LeaveAMessageForm: public Fastcgipp::Request<wchar_t>
{
public:
    LeaveAMessageForm() :
        db(NULL)
    {}

    ~LeaveAMessageForm() {
        sqlite3_close(db);
        db = NULL;
    }
private:
    sqlite3 * db;
private:
    bool response()
    {
        using namespace Fastcgipp;

        int rc = sqlite3_open("message_data.db", &db);
        if(rc != 0) {
            sqlite3_close(db);
            db = NULL;

            char buf[1024];
            snprintf(buf, 1024, "Cannot open database: %s", sqlite3_errmsg(db));
            error_log(buf);
            throw std::runtime_error(buf);
        }//if

        std::vector<std::string> formdata(9);
        for(int i = 4; i <= 7; ++i)
            formdata[i] = "0";

        // get id
        {
            char * zErrMsg = NULL;
            std::string command = "SELECT MessagesID FROM idTable;";
            int rc = sqlite3_exec(db, command.c_str(), db_callback_select_id, 0, &zErrMsg);
            if(rc != SQLITE_OK) {
                std::string errmsg("select MessageID: ");
                errmsg += zErrMsg;

                sqlite3_free(zErrMsg);
                error_log(errmsg.c_str());
                throw std::runtime_error(errmsg.c_str());
            }//if
        }
        {
            char buf[5];
            snprintf(buf, 5, "%04d", g_id);
            formdata[0] = std::string(buf);
        }

        wchar_t cookieString[] = { '<', '"', 0x0440, 0x0443, 0x0441, 0x0441, 0x043a, 0x0438, 0x0439, '"', '>', ';', 0x0000 };
        out << "Set-Cookie: echoCookie=" << encoding(URL) << cookieString << encoding(NONE) << "; path=/\n";
        out << "Content-Type: text/html; charset=utf-8\r\n\r\n";
        out << "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />";
        out << "<title>fastcgi++: </title></head><body>";
        out << "<h1>Environment Parameters</h1>";
        out << "<p><b>FastCGI Version:</b> " << Protocol::version << "<br />";
        out << "<b>fastcgi++ Version:</b> " << version << "<br />";
        out << "<b>Hostname:</b> " << encoding(HTML) << environment().host << encoding(NONE) << "<br />";
        out << "<b>User Agent:</b> " << encoding(HTML) << environment().userAgent << encoding(NONE) << "<br />";
        out << "<b>Accepted Content Types:</b> " << encoding(HTML) << environment().acceptContentTypes << encoding(NONE) << "<br />";
        out << "<b>Accepted Languages:</b> " << encoding(HTML) << environment().acceptLanguages << encoding(NONE) << "<br />";
        out << "<b>Accepted Characters Sets:</b> " << encoding(HTML) << environment().acceptCharsets << encoding(NONE) << "<br />";
        out << "<b>Referer:</b> " << encoding(HTML) << environment().referer << encoding(NONE) << "<br />";
        out << "<b>Content Type:</b> " << encoding(HTML) << environment().contentType << encoding(NONE) << "<br />";
        out << "<b>Root:</b> " << encoding(HTML) << environment().root << encoding(NONE) << "<br />";
        out << "<b>Script Name:</b> " << encoding(HTML) << environment().scriptName << encoding(NONE) << "<br />";
        out << "<b>Request URI:</b> " << encoding(HTML) << environment().requestUri << encoding(NONE) << "<br />";
        out << "<b>Request Method:</b> " << encoding(HTML) << environment().requestMethod << encoding(NONE) << "<br />";
        out << "<b>Content Length:</b> " << encoding(HTML) << environment().contentLength << encoding(NONE) << "<br />";
        out << "<b>Keep Alive Time:</b> " << encoding(HTML) << environment().keepAlive << encoding(NONE) << "<br />";
        out << "<b>Server Address:</b> " << encoding(HTML) << environment().serverAddress << encoding(NONE) << "<br />";
        out << "<b>Server Port:</b> " << encoding(HTML) << environment().serverPort << encoding(NONE) << "<br />";
        out << "<b>Client Address:</b> " << encoding(HTML) << environment().remoteAddress << encoding(NONE) << "<br />";
        out << "<b>Client Port:</b> " << encoding(HTML) << environment().remotePort << encoding(NONE) << "<br />";
        out << "<b>If Modified Since:</b> " << encoding(HTML) << environment().ifModifiedSince << encoding(NONE) << "</p>";
        out << "<h1>Path Data</h1>";
        if(environment().pathInfo.size()) {
            std::wstring preTab;
            for(Http::Environment<wchar_t>::PathInfo::const_iterator it=environment().pathInfo.begin(); it!=environment().pathInfo.end(); ++it) {
                out << preTab << encoding(HTML) << *it << encoding(NONE) << "<br />";
                preTab += L"&nbsp;&nbsp;&nbsp;";
            }//for
        } else {
            out << "<p>No Path Info</p>";
        }//if-else
        out << "<h1>GET Data</h1>";
        if(environment().gets.size()) {
            for(Http::Environment<wchar_t>::Gets::const_iterator it=environment().gets.begin(); it!=environment().gets.end(); ++it)
                out << "<b>" << encoding(HTML) << it->first << encoding(NONE) << ":</b> " << encoding(HTML) << it->second << encoding(NONE) << "<br />";
        } else {
            out << "<p>No GET data</p>";
        }//if-else

        out << "<h1>Cookie Data</h1>";
        if(environment().cookies.size()) {
            for(Http::Environment<wchar_t>::Cookies::const_iterator it=environment().cookies.begin(); it!=environment().cookies.end(); ++it)
                out << "<b>" << encoding(HTML) << it->first << encoding(NONE) << ":</b> " << encoding(HTML) << it->second << encoding(NONE) << "<br />";
        } else {
            out << "<p>No Cookie data</p>";
        }//if-else
        out << "<h1>POST Data</h1>";
        if(environment().posts.size()) {
            for(Http::Environment<wchar_t>::Posts::const_iterator it=environment().posts.begin(); it!=environment().posts.end(); ++it) {
                out << "<h2>" << encoding(HTML) << it->first << encoding(NONE) << "</h2>";
                if(it->second.type==Http::Post<wchar_t>::form) {
                    out << "<p><b>Type:</b> form data<br />";
                    out << "<b>Value:</b> " << encoding(HTML) << it->second.value << encoding(NONE) << "</p>";

                    // update form data
                    updateFormData(formdata, it->first, it->second.value);
                } else {
                    out << "<p><b>Type:</b> file<br />";
                    out << "<b>Filename:</b> " << encoding(HTML) << it->second.filename << encoding(NONE) << "<br />";
                    out << "<b>Content Type:</b> " << encoding(HTML) << it->second.contentType << encoding(NONE) << "<br />";
                    out << "<b>Size:</b> " << it->second.size() << "<br />";
                    out << "<b>Data:</b></p><pre>";
                    out.dump(it->second.data(), it->second.size());
                    out << "</pre>";
                }//if-else
            }//for
        } else {
            out << "<p>No POST data</p>";
        }//if-else
        out << "<hr/>";
        out << "</body></html>";

        // insert the message into table
        {
            char * zErrMsg = NULL;
            std::string command = "INSERT INTO Messages(id, "
                "name, email, gender, football, music, dancing, comics, message) "
                "VALUES (";
            for(int i = 0; i < 8; ++i)
                command += '\'' + formdata[i] + "', ";
            command += '\'' + formdata[8] + "');";
            int rc = sqlite3_exec(db, command.c_str(), db_callback_insert, 0, &zErrMsg);
            if(rc != SQLITE_OK) {
                std::string errmsg("insert into Messages: ");
                errmsg += zErrMsg;

                char buf[1024];
                snprintf(buf, 1024, " db: %p", db);
                errmsg += buf;
                errmsg += " command: ";
                errmsg += command;

                sqlite3_free(zErrMsg);
                error_log(errmsg.c_str());
                throw std::runtime_error(errmsg.c_str());
            }//if
        }
        
        // update id
        {
            char buf[5];
            snprintf(buf, 5, "%04d", g_id + 1);

            char * zErrMsg = NULL;
            std::string command = std::string("UPDATE idTable SET MessagesID='") + buf + "'";
            int rc = sqlite3_exec(db, command.c_str(), db_callback_update_id, 0, &zErrMsg);
            if(rc != SQLITE_OK) {
                std::string errmsg("update idTable: ");
                errmsg += zErrMsg;

                sqlite3_free(zErrMsg);
                error_log(errmsg.c_str());
                throw std::runtime_error(errmsg.c_str());
            }//if
        }

        sqlite3_close(db);
        db = NULL;

        return true;
    }
};

// The main function is easy to set up
int main()
{
    try {
        Fastcgipp::Manager<LeaveAMessageForm> fcgi;
        fcgi.handler();
    } catch(std::exception & e) {
        error_log(e.what());
    }//try-catch

    return 0;
}

