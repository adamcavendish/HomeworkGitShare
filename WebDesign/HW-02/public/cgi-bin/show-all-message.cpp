// C-standard
#include <cstring>
// STL
#include <fstream>
#include <vector>
#include <stdexcept>
// Boost
#include <boost/date_time/posix_time/posix_time.hpp>
// FastCGI++
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>
// Sqlite3
#include <sqlite3.h>

std::vector<std::vector<std::string> > g_dbdata;

void error_log(const char* msg) {
    using namespace std;
    using namespace boost;
    static ofstream error;
    if(!error.is_open()) {
        error.open("/tmp/errlog", ios_base::out | ios_base::app);
        error.imbue(locale(error.getloc(), new posix_time::time_facet()));
    }//if
    error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}//error_log(msg)

static int db_callback(void * NotUsed, int argc, char ** argv, char ** azColName) {
    (void)(NotUsed);
    (void)(azColName);

    g_dbdata.push_back(std::vector<std::string>());
    g_dbdata.back().reserve(9);

    for(int i = 0; i < argc; ++i) {
        g_dbdata.back().push_back(argv[i] ? argv[i] : "NULL");
    }//for

    return 0;
}//db_callback(NotUsed, argc, argv, azColName)

class ShowAllMessageAJAX: public Fastcgipp::Request<wchar_t>
{
public:
    ShowAllMessageAJAX() :
        db(NULL)
    {
        int rc = sqlite3_open("message_data.db", &db);
        if(rc) {
            sqlite3_close(db);
            db = NULL;
            char buf[1024];
            snprintf(buf, 1024, "Cannot open database: %s\n", sqlite3_errmsg(db));
            throw std::runtime_error(buf);
        }//if
    }

    ~ShowAllMessageAJAX() {
        sqlite3_close(db);
        db = NULL;
    }
private:
    sqlite3 * db;

    bool response() {
        g_dbdata.clear();

        char * zErrMsg = NULL;
        std::string command = "SELECT * FROM Messages;";
        int rc = sqlite3_exec(db, command.c_str(), db_callback, 0, &zErrMsg);
        if(rc != SQLITE_OK) {
            sqlite3_free(zErrMsg);
        }//if

        out << "Content-Type: text/html; charset=utf-8\r\n\r\n";
        /*
        out << "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />";
        out << "<title>All Messages</title></head><body>";
        */
        out << "<html><body>";
        out << "<h2>All Messages: </h2>";
        out << "<div><table border='1' class='table-allMessages'>";
        // print the column name
        char buf[1024];
        snprintf(buf, 1024,
                "<tr><th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th></tr>\n",
                "id", "name", "email", "gender", "football", "music",
                "dancing", "comics", "message");
        out << buf;
        // print all messages
        for(std::size_t i = 0; i < g_dbdata.size(); ++i) {
            if(g_dbdata[i].size() != 9)
                throw std::runtime_error("g_dbdata's data size not equal to 9!");
            snprintf(buf, 1024,
                    "<tr><td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td></tr>\n",
                    g_dbdata[i][0].c_str(),
                    g_dbdata[i][1].c_str(),
                    g_dbdata[i][2].c_str(),
                    g_dbdata[i][3].c_str(),
                    g_dbdata[i][4].c_str(),
                    g_dbdata[i][5].c_str(),
                    g_dbdata[i][6].c_str(),
                    g_dbdata[i][7].c_str(),
                    g_dbdata[i][8].c_str());
            out << buf;
        }//for
        out << "</table></div>";

        out << "</body></html>";

        return true;
    }
};

// The main function is easy to set up
int main()
{
    try {
        Fastcgipp::Manager<ShowAllMessageAJAX> fcgi;
        fcgi.handler();
    } catch(std::exception& e) {
        error_log(e.what());
    }//try-catch

    return 0;
}

