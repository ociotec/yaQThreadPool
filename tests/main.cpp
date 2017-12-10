/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include <gtest/gtest.h>
#include <QLoggingCategory>
#include <QString>
#include <QtGlobal>


int main(int argc, char **argv)
{
    qSetMessagePattern(QStringLiteral("             ["
                                      "%{if-debug}\e[37mDEBUG\e[0m%{endif}"
                                      "%{if-info}\e[96mINFO \e[0m%{endif}%"
                                      "{if-warning}\e[93mWARN \e[0m%{endif}"
                                      "%{if-critical}\e[91mERROR\e[0m%{endif}"
                                      "%{if-fatal}\e[95mFATAL\e[0m%{endif}"
                                      " %{time yyyy/MM/dd hh:mm:ss.zzz} #%{threadid}] "
                                      "%{message}"));
    QLoggingCategory::setFilterRules("*.debug=true\n"
                                     "*.info=true\n"
                                     "*.warning=true\n"
                                     "*.error=true\n"
                                     "*.critical=true\n"
                                     "*.ssl.warning=false");
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
