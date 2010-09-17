/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package zad2;

import java.io.File;

/**
 *
 * @author batas2
 */
public class DirThread implements Runnable {

    private String _file;
    private File _dir = null;
    private DirHistory _dirHistory = null;

    private void _searchDir(String destFile, File Dir) {
        File[] files = Dir.listFiles();

        for (File file : files) {
            if (file.isDirectory() && _dirHistory.Check(file.toString())) {
                _searchDir(destFile, file);
            }
            if (file.getName().matches(destFile)) {
                System.out.println(Thread.currentThread().getName() + ": " + file);
            }
        }

    }

    public DirThread(String File, String Dir, DirHistory dirHistory) {
        _dir = new File(Dir);
        _file = File;
        _dirHistory = dirHistory;
    }

    public void run() {
        if (_dir.exists()) {
            _searchDir(_file, _dir);
        }
    }
}
