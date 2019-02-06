import sys
import os

ALLSOURCES="src/DataSet.cpp src/Scale.cpp src/Color.cpp src/Configuration.cpp src/OutputGrid.cpp src/IOVector.cpp" \
            + " src/CairoDrawer.cpp src/Scene.cpp src/Utils.cpp src/InputAxis.cpp"
TESTDIR="test/"
EXEDIR=TESTDIR + "exe/"
EXEPRE="test"
ALL={"coordinates":"CoordinatesTest.cpp", "configuration":"ConfigurationTest.cpp","dataset":"DataSetTest.cpp", \
     "storage":"StorageElementsTest.cpp", "utilities":"UtilitiesTest.cpp", "graphical": "GraphicalElementsTest.cpp"}

def execute_tests(test_v):
    print "Making directory \"test/exe\"..."
    os.system("mkdir -p test/exe")
    
    print "Building libsource.so..." 
    exit_val = os.system(r"g++ -std=c++11 -fPIC -shared " \
                  + "-I/home/IBT/stratmann/Dokumente/MooViE/include " \
                  + "-I/usr/include/cairomm-1.0/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/ " \
                  + "-I/usr/include/sigc++-2.0/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ " \
                  + "-I/usr/include/cairo/ " \
                  + "-I/usr/include/freetype2/ " \
                  + "-L/usr/lib/x86_64-linux-gnu/ -o " \
                  + EXEDIR + "libsource.so " + ALLSOURCES + " -lcairo -lcairomm-1.0" )
     
    if exit_val != 0:
        exit("Exit due to compile time error")
        
    print "Building and running tests..."
        
    failed = 0
    for option in test_v:
        print ">> " + option + ":",
        if os.system(r"g++ -std=c++11 -I/home/IBT/stratmann/Dokumente/MooViE/include " \
                  + "-L/home/IBT/stratmann/Dokumente/MooViE/test/exe/ " \
                  + "-L/largestorage/cluster_root/usr/lib/x86_64-linux-gnu/ -o " \
                  + EXEDIR + EXEPRE + option + " " \
                  + TESTDIR + ALL[option] \
                  + " -lsource " + "-lboost_unit_test_framework" ) == 0:
            if os.system(r"LD_LIBRARY_PATH=/largestorage/cluster_root/usr/lib/x86_64-linux-gnu/" \
                  + ":/home/IBT/stratmann/Dokumente/MooViE/test/exe/ ./" \
                  + EXEDIR + EXEPRE + option + " > " + EXEDIR + option + ".log 2>&1") == 0:
                print "success"
            else:
                failed += 1
                print "failure"
            
    return failed
    
if __name__=='__main__':
    if len(sys.argv) > 1:
        test_vector = []
        abort = False
        for i in range(1,len(sys.argv)):
            if sys.argv[i] not in ALL:
                if sys.argv[i] == 'all':
                    test_vector = [i for i in ALL]
                elif sys.argv[i] == 'help':
                    print("Options are: " + str(ALL))
                    abort = True
                else:
                    abort = True
                    print "Unknown option: " + sys.argv[i]
                    break
            else:
                test_vector.append(sys.argv[i])

        if not abort:
            failed = execute_tests(test_vector)
            if failed == 0:
                print "=== All tests were passed"
            else:
                print "=== " + str(failed) + " tests were not passed"
    else:
        print "Need option to execute"
