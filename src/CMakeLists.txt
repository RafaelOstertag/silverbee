set(sources 
            alarmsettingswindow.cxx
            alarmsettings.cxx
            background.cxx
            mainwindow.cxx
            silverbee.cxx
            sound.cxx
            state/alarmcontext.cxx
            state/armed.cxx
            state/snoozing.cxx
            state/sounding.cxx
)

add_executable(silverbee ${sources})
target_compile_options(silverbee PRIVATE ${GTKMM_CFLAGS_OTHER} ${GST_CFLAGS_OTHER})
target_include_directories(silverbee PUBLIC ${GTKMM_INCLUDE_DIRS} ${GST_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})
target_link_libraries(silverbee ${GTKMM_LDFLAGS} ${GST_LDFLAGS} -pthread)

