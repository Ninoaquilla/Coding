public class Java6_1 {
    public void main (String[] args) {
        int[] umur = {14, 15, 16, 17, 18, 19};
        String[] NamaS = {"Subjek1", "Subjek2", "Subjek3"};
        
        System.out.println(umur[0]);
        System.out.println(NamaS[2]);
        System.out.println("");

        for (int U : umur) {
            System.out.println(U);
        }
        System.out.println("");
        for (String N : NamaS) {
            System.out.println(N);
        }
    }
}
