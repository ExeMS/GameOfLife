<!DOCTYPE html>
<html>
<body>

<canvas id="myCanvas" width="500" height="500"
style="border:1px solid #000000;">
</canvas>

</body>
</html>

<script>
cellrow = 60;
function CreateBoard(cellrow){
	board = new Array(cellrow);
   	for(x = 0; x < cellrow; x++){

    	board[x] = new Array(cellrow);


    	for(y = 0; y < cellrow; y++){
        	board[x][y] = Math.floor(Math.random() * 2);
            }
        }
    return board;
    }
function draw(){
   	for(x = 0; x < cellrow; x++){
   		for(y = 0; y < cellrow; y++){
        	if (board[x][y] == 1){
            	ctx.fillRect(x*size,y*size,size,size);
                }
            }
    }
    	
}
function counting(){
	nboard = [];
   	for(x = 0; x < cellrow; x++){

    	nboard[x] = new Array(cellrow);


    	for(y = 0; y < cellrow; y++){
        	nboard[x][y] = board[x][y];
            neighbours = findneighbours(x,y);
            if (neighbours == 3){
            	nboard[x][y] = 1
                }
            if (neighbours < 2){
            	nboard[x][y] = 0;
                }
            if (neighbours > 3){
            	nboard[x][y] = 0;
                }
                
      
            }
        }
        return nboard
    
}

function findneighbours(x,y){
	total = 0
   	for(i = -1; i < 2; i++){
   		for(j = -1; j < 2; j++){
        	row = (x+i +cellrow)%cellrow;
            column = (y+j+cellrow)%cellrow;
            total += board[row][column];
         
            
        
       }
    }
    return total
}

function frame(board){
	ctx.clearRect(0,0,500,500);
    draw();
    var nboard = counting();
    board = nboard;
    window.requestAnimationFrame(frame(board));
}
var canvas = document.getElementById("myCanvas");
var ctx = canvas.getContext("2d");
const size = 500/cellrow;
var board = CreateBoard(cellrow);
draw();
window.requestAnimationFrame(frame(board));

</script>
