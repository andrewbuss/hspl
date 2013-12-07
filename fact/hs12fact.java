import java.util.Scanner;
import java.io.*;

class Main{
	List<List<int>> factors = new ArrayList<List<int>>(100001);
	public static void factorize(int in) {
		int n = in;
		List<int> mfactors = new ArrayList<int>();
		for (int i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				mfactors.add(i);
				n /= i;
			}
		}
		if (n > 1) {
			mfactors.add(n);
		}
		factors[in] = mfactors;
	}
	public static void main (String[] args){
		Scanner in = new Scanner(System.in);
		int ntests = in.nextInt();
		for(int t = 0;t<ntests;t++){
			List<int> bins = new ArrayList<int>(100001);
			int an = in.nextInt();
			for(int i=0;i<an;i++){
				int j = in.nextInt();
				if(factors[j].isEmpty()) factorize(j);
				System.out.println(
				for(int k:factors[j]){
					bins[k]++;
				}
			}
			System.out.println(x.subtract(BigInteger.ONE).toString());
		}
	}
}