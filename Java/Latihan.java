import java.util.Scanner;

public class Latihan {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {  // Scanner akan otomatis tertutup
            System.out.print("Masukkan nama kamu: ");
            String nama = scanner.nextLine();

            System.out.print("Masukkan umur kamu: ");
            int umur = scanner.nextInt();

            if (umur < 13) {
                System.out.println("Hai " + nama + ", kamu masih kecil.");
            } else if (umur <= 19) {
                System.out.println("Hai " + nama + ", kamu seorang remaja.");
            } else {
                System.out.println("Hai " + nama + ", kamu sudah dewasa.");
            }
        } // Scanner akan otomatis tertutup di sini
    }
}
