class Foda {
	private static boolean isConsecutiveGt(int a, int b, int c) {
		return a > b && b > c;
	}
	
	private static int minimumDeletions(int a[], int n) { 
	    if (n <= 2) 
	        return 0; 
	  
	    // If number of element 
	    // is greater than 2. 
	    int count = 0; 
	    for (int i = 0; i < n - 2; i++) 
	    { 
	        // If three element are  
	        // consecutively increasing 
	        // or decreasing. 
	        if (isConsecutiveGt(a[i], a[i+1], a[i+2]) ||
	             isConsecutiveGt(-a[i], -a[i+1], -a[i+2])) 
	            count++; 
	    } 
	  
	    return count; 
	} 
	  
	// Driver Code 
	public static void main (String[] args)  
	{ 
	    int a[] = { 23, 12, 46, 64, 50, 56}; 
	    int n = a.length; 
	  
	    System.out.println(minimumDeletions(a, n)); 
	} 
}