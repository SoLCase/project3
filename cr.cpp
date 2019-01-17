
	class Student{
    public:
    	int bomb(int matrix[5][6]);
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor)
		{
			int predict[5][6];
			int possible_move=0;
			Color enemy;
			double prioritymap[5][6];
			if(inputColor==Blue)
			{
				enemy=Red;
			}
			else
			{
				enemy=Blue;
			}
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<6;j++)
				{
					if(color[i][j]!=enemy||color[i][j]==Black)
					{
						possible_move=possible_move+0;
					}
					else possible_move++;
				}
			}
			bool bombmap[5][6];
			//set every cell as a bomb or not
			for(int i=0;i<5;i++)
              {for(int j=0;j<6;j++)
              {
              	if(Max[i][j]-Record[i][j]==1)
              	{
              		bombmap[i][j]=true;                                     
			   }
			   else {
			   	bombmap[i][j]=false;
			   }
				}
              }
             
			 //set every cell's priority corner=1 edge=2 middle=3
            for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            	prioritymap[i][j]=Max[i][j]-1;
				}
			}
            
            //bomb is my weapon unless special situation i don't use it
            for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            	if(bombmap[i][j]==true)
            	{prioritymap[i][j]=40;}
				}
			}
			// the most situation an enemy's bomb near my bomb i should explode it,so make it very early
				for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            	// here is my bomb
            		if(color[i][j]==inputColor&& bombmap[i][j]==true)
            		{
            			// if any enemy's bomb besides it it will explode very early
            			if(i>0)
            			{if(color[i-1][j]==enemy&& bombmap[i-1][j]==true)
            			{prioritymap[i][j]=0;}}
            			
            			if(i<4){if(color[i+1][j]==enemy&& bombmap[i+1][j]==true)
            			{prioritymap[i][j]=0;}}
            			
            			if(j>0) {if(color[i][j-1]==enemy&& bombmap[i][j-1]==true)
            			{prioritymap[i][j]=0;}}
            			
            			if(j<5) {if(color[i][j+1]==enemy&& bombmap[i][j+1]==true)
            			{prioritymap[i][j]=0;}}
 
					}
				}
			}
			// now c:1 e:2 m:3 b:40
			// the enemy's bomb near my bomb :0			
			// avoid enemy's bomb or destroy it by my bomb near it(call it destroyer)
              for(int i=0;i<5;i++)
              {for(int j=0;j<6;j++)
              {
              	//here is enemy's bomb
                 if(bombmap[i][j]==true&&color[i][j]==enemy)
                 {
                 	 if(i>0)
            			{if(bombmap[i-1][j]==true&&color[i-1][j]==inputColor)
                 	{
                 		// destroyer<=0 so it will be the first choose.
                 		prioritymap[i-1][j]-=3;
					}
					else if(bombmap[i-1][j]==false)
					{
						//should avoid it  now is corner=4 e=5 m=6 
						prioritymap[i-1][j]+=2.5;
					}}
					if(i<4){
					if(bombmap[i+1][j]==true&&color[i+1][j]==inputColor)
                 	{
                 		prioritymap[i+1][j]-=3;
					}
					else if(bombmap[i+1][j]==false)
					{
						prioritymap[i+1][j]+=2.5;
					}}
					if(j>0) {
					if(bombmap[i][j-1]==true&&color[i][j-1]==inputColor)
                 	{
                 		prioritymap[i][j-1]-=3;
					}
					else if(bombmap[i][j-1]==false)
					{
						prioritymap[i][j-1]+=2.5;
					}}
					if(j<5) {
					if(bombmap[i][j+1]==true&&color[i][j+1]==inputColor)
                 	{
                 		prioritymap[i][j+1]-=3;
					}
					else if(bombmap[i][j+1]==false)
					{
						prioritymap[i][j+1]+=2.5;
					}}
				 }
			  }}
			  //now normal                    corner:1 e=2 m=3 b=40
		      //    nearenemybomb(call it useless) c:4 e=5 m=6 b=-3
			  
			  //for my bomb every cell near it is "protected" if enemy move to here i can destroy it.
			  // so here i can move to it later
			  for(int i=0;i<5;i++)
			  {
			  	for(int j=0;j<6;j++)
			  	{
			  		//here is my bomb 
			  		if(bombmap[i][j]==true&&color[i][j]==inputColor)
			  		{
			  		if(i>0)
            			{
			  			if(bombmap[i-1][j]==true&&color[i-1][j]==enemy)
                 	{
                 		//if an enemy's bomb near my bomb make it explode early
                 		prioritymap[i][j]-=3;
					}
					else if(bombmap[i-1][j]==false&&color[i-1][j]!=enemy)
					{
						//if my bomb near it move to her later
						prioritymap[i-1][j]+=3.1;
					}}
					if(i<4){
					if(bombmap[i+1][j]==true&&color[i+1][j]==enemy)
                 	{
                 		
                 		prioritymap[i][j]-=3;
					}
					else if(bombmap[i+1][j]==false&&color[i+1][j]!=enemy)
					{
						prioritymap[i+1][j]+=3.1;
					}}
					if(j>0) {
					if(bombmap[i][j-1]==true&&color[i][j-1]==enemy)
                 	{
                 		prioritymap[i][j]-=3;
					}
					else if(bombmap[i][j-1]==false&&color[i][j-1]!=enemy)
					{
						prioritymap[i][j-1]+=3.1;
					}}
					if(j<5) {
					if(bombmap[i][j+1]==true&&color[i][j+1]==enemy)
                 	{
                 		prioritymap[i][j]-=3;
					}
					else if(bombmap[i][j+1]==false&&color[i][j+1]!=enemy)
					{
						prioritymap[i][j+1]+=3.1;
					}}
					}
				 }
			  }
			  //after this : normal c=1 e=2 m=3 b=40
			  //             useless c:4 e=5 m=6 b=-3
			  //             protected c:4 e=5 m=6
			  // if a cell both as useless and protected?  it will be choose very late 
			  // if my bomb near enemy's bomb? my bomb will explode very early
			  
			  // for dangerous cell it means if an enemy cell now is not a bomb but will be bomb sooner than it's neighbor i should avoid to be it's neighbor.
			for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            	  if(color[i][j]==enemy)
            	  {//how fast this enemy's cell become a bomb
            	  	int mid=Max[i][j]-Record[i][j];
            	  	//how fast this cell's neighbor becomes a bomb.
            	  	int left=Max[i-1][j]-Record[i-1][j];
            	  	int right=Max[i+1][j]-Record[i+1][j];
            	  	int down=Max[i][j+1]-Record[i][j+1];
            	  	int up=Max[i][j-1]-Record[i][j-1];
            	  	//if mid faster than neighbor don't choose neighbor
            	  	 if(i>0)
            			{
            	  	if(mid<=left)
            	  	{
            	  		prioritymap[i-1][j]+=3;
					}}
            	  	if(i<4){
            	  	if(mid<=right)
            	  	{
            	  		prioritymap[i+1][j]+=3;
					  }}
            	  	if(j>0) {
            	  	if(mid<=up)
            	  	{
            	  		prioritymap[i][j-1]+=3;
					  }}
            	  	if(j<5) {
            	  	if(mid<=down)
            	  	{
            	  		prioritymap[i][j+1]+=3;
					  }}
				  }
				}
			}
			//AFTER it normal: c:1 e:2 m:3 b:40
			//         dangerous: c:4 e:5 m:6 b:43
			//         protected: c:4 e:5 m:6 
			//         useless: c:4 e:5 m:6 b:-3
		  // i don't care about which is early in normal situation  only need to care about bomb.
		  
		  //ta cell which surrounded by enemy's bomb should move early than a cell surrounded by my bomb
		   	for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            		if(color[i][j]!=Black&&color[i][j]!=enemy)
            		{
            			if(i>0)
            			{
            				if(bombmap[i-1][j]==true&&color[i-1][j]==enemy)
            				{
            					prioritymap[i][j]-=2;
							}
							else if(bombmap[i-1][j]==true&&color[i-1][j]==inputColor)
							{
								prioritymap[i][j]+=25;
							}
						}
            			if(i<4)
            			    {	if(bombmap[i+1][j]==true&&color[i+1][j]==enemy)
            				{
            					prioritymap[i][j]-=2;
							}
							else if(bombmap[i+1][j]==true&&color[i+1][j]==inputColor)
							{
								prioritymap[i][j]+=2;
							}}
            			if(j>0)
            			   {	if(bombmap[i][j-1]==true&&color[i][j-1]==enemy)
            				{
            					prioritymap[i][j]-=2;
							}
							else if(bombmap[i][j-1]==true&&color[i][j-1]==inputColor)
							{
								prioritymap[i][j]+=2;
							}}
            			if(j<5)
            			  {	if(bombmap[i][j+1]==true&&color[i][j+1]==enemy)
            				{
            					prioritymap[i][j]-=2;
							}
							else if(bombmap[i][j+1]==true&&color[i][j+1]==inputColor)
							{
								prioritymap[i][j]+=2;
							}}
					}
				}
			}

		  // can't not move to enemy's and wall
		  			for(int i=0;i<5;i++)
            {
            	for(int j=0;j<6;j++)
            	{ 
            		if(color[i][j]==Black||color[i][j]==enemy)
            		{
            			prioritymap[i][j]=99999;
					}
				}
			}
			
			//choose the earlist
			  int temp=99998;
			  int choosex;int choosey;
			  for(int i=0;i<5;i++)
			  {
			  	for(int j=0;j<6;j++)
			  	{
			  		if (prioritymap[i][j]<temp)
			  		{
			  			temp=prioritymap[i][j];
			  			choosex=i;choosey=j;
					  }
				 }
			  }
			  x=choosex;y=choosey;
			  
        };
        int getX()
        {
            return x;
 };
        int getY()
        {
	return y;
};
    private:
        int x;
        int y;
    };

