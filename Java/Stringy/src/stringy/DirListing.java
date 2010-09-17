/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stringy;

import java.io.File;

/**
 *
 * @author batas2
 */
public class DirListing {

    private String _src;

    public DirListing(String src) {
        _src = src;
    }

    private void doListing(String src, int v) {
        File dir = new File(src);
        if (dir.isDirectory()) {
            for (String s : dir.list()) {
                File f = new File(src + "/" + s);
                if (f.isDirectory()) {
                    doListing(src + "/" + s, v + 1);
                }
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < v; i++) {
                    sb.append('-');
                }
                sb.append(s);
                System.out.println(sb);


            }
        }
    }

    public void List() {
        doListing(_src, 1);
    }
}
