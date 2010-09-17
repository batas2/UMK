package stringy;

import java.io.*;
import java.util.*;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void Iniclay() {
        String s = new String();
        s = "Bartosz Frackowiak";
        String tab[] = new String[2];
        tab = s.split(" ");

        System.out.println(String.valueOf(tab[0].charAt(0)) + String.valueOf(tab[1].charAt(0)));
    }

    public static void Konkatenacja() {
        String a = "abc";
        String b = "def";
        System.out.println(a + b + 43 + 27);
        System.out.println(26 + a + 43 + b);
        System.out.println(26 + 43 + a + b);
    }

    public static void Anagram() {

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        String str1 = new String();
        String str2 = new String();

        try {
            str1 = in.readLine();
            str2 = in.readLine();
        } catch (IOException e) {
            System.out.print(e);
        }

        char[] str1c = str1.toCharArray();
        char[] str2c = str2.toCharArray();

        Arrays.sort(str1c);
        Arrays.sort(str2c);

        if (Arrays.equals(str1c, str2c)) {
            System.out.println("sa anagramami");
        } else {
            System.out.println("Nie sa anagramami");
        }
    }

    public static void Litery(char v) {

        BufferedReader in = null;
        try {
            in = new BufferedReader(new InputStreamReader(new FileInputStream("/home/batas2/plik.txt")));
        } catch (FileNotFoundException ex) {
            System.out.print(ex);
        }

        String str = new String();
        int c = 0;

        try {
            if (in != null) {
                while ((str = in.readLine()) != null) {
                    for (int i = 0; i < str.length(); i++) {
                        if (str.charAt(i) == v) {
                            c++;
                        }
                    }
                }
            }
        } catch (IOException e) {
            System.out.print(e);
        }
        System.out.print(c);
    }

    public static void main(String[] args) {
        //wystapienia litery w pliku
        //listuje zawartosc katalogu
        // Iniclay();
        // Konkatenacja();
        // Anagram();
        Litery('q');
        DirListing d = new DirListing("/home/batas2/UMK/Java");
        d.List();
    }
}
