import java.io.*;
import java.util.*;
import java.awt.geom.*;

public class Main
{
    public Scanner sc;
    public PrintStream ps;

    public int maxlevel = 0;
    public char generators[] = new char[15];
    
    public String generate( int level )
    {
        String result = "";
        
        if( level>0 )
        {
            --level;
            result = generate(level) + generators[level] + generate(level);
        }
                
        return result;
    }
    
    /**
     * Driver.
     * @throws Exception
     */
    public void doit() throws Exception
    {
        sc = new Scanner(System.in);
        ps = new PrintStream(System.out);
        
        // These are legitimate lengths.
        // They are powers of 2 minus 1
        int legit[] = new int[20];
        for( int i=0; i<20; i++ )
        {
            legit[i] = (1<<i)-1;
        }
        
        // See which of the ten digits are available for the first place
        boolean avail[] = new boolean[10];

        for(;;)
        {           
            // There are a number of ways we can fail.
            // We'll use this variable to see if any of the happens.
            boolean fail = true;
            
            long n = sc.nextLong();
            if( n==0L ) break;

            char digits[] = sc.next().trim().toCharArray();
            
            // We fail if the digit string isn't of the right length.
            for( int i=0; i<20 && fail; i++ )
            {
                if( digits.length == legit[i] ) fail = false;
            }
                       
            if( !fail )
            {
                Arrays.fill( generators, '-' );
                maxlevel = 0;
                for( int i=0; i<digits.length; i++ )
                {
                    int level = 1;
                    int k = i+1;
                    while( (k&1)==0 )
                    {
                        k >>= 1;
                        level++;
                    }
                    if( level>maxlevel ) maxlevel = level;
                    --level;
                    
                    if( generators[level]=='-' || generators[level]=='?' ) generators[level] = digits[i];
                    if( generators[level]!=digits[i] ) fail = true;
                }
                
                if( generators[0]=='0' ) fail = true;
                if( Character.isDigit( generators[0] )) for( int i=1; i<maxlevel; i++ )
                {
                    if( generators[i]==generators[0] ) fail = true;
                }
            }
            
            String base9str = Long.toString( n-1, 9 );
            int need = 0;
            for( int i=0; i<maxlevel; i++ )
            {
                if( generators[i]=='?' ) ++need;
            }
            
            if( need==0 && n!=1 ) fail=true;
            if( need>0 && need<base9str.length() )fail = true;
            String pad = "00000000000000000000" + base9str;
            char base9[] = pad.substring( pad.length()-need, pad.length() ).toCharArray();          
            
            int p=0;
            
            // The first digit is special.
            if( digits[0]=='?' )
            {
                // This array will show which digits are available for digit 1
                Arrays.fill( avail, true );
                avail[0] = false;
                
                // If any digit has been used anywhere else in the number,
                // then it's not available for the 1st digit
                for( int i=0; i<maxlevel; i++ )
                {
                    if( generators[i]!='?' ) avail[(int)(generators[i]-'0')] = false;
                }
                
                int count = (int)(base9[p++]-'0');
                int digit = 1;
                while( digit<10 && !avail[digit] ) ++digit;
                for( int i=0; i<count; i++ )
                {
                    ++digit;
                    while( digit<10 && !avail[digit] ) ++digit;
                }
                
                if( digit<10 ) digits[0] = generators[0] = (char)(digit+'0'); 
                else fail = true;
            }
            
            if( !fail ) for( int i=1; i<digits.length; i++ ) if( digits[i]=='?' )
            {
                int j = i+1;
                int g = 0;
                while( (j&1)==0 )
                {
                    ++g;
                    j>>=1;
                }
                
                if( generators[g]=='?' )
                {
                    char ch = base9[p++];
                    if( generators[0]<=ch ) ++ch;
                    generators[g] = digits[i] = ch;
                }
                else
                {
                    digits[i] = generators[g];
                }
            }            
            ps.println( fail ? "-1" : new String( digits ) );
        }
    }
    
    /**
     * @param args
     */
    public static void main( String[] args ) throws Exception
    {
        new Main().doit();
    }   
}
