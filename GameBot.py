#GameBot
import os
from random import randint as r
from time import sleep as s
import discord
from discord.ext import commands
from discord import Webhook, AsyncWebhookAdapter
from dotenv import load_dotenv
import aiohttp

gol = False
class GoL:
    def __init__(self, board, rows, columns):
        self.board = board
        self.rows = rows
        self.columns = columns
    def findOutput(self):
        outputList = []
        for i in range(self.rows):
            output = ''
            for j in range(self.columns):
                if self.board[i][j].state == 0:
                    output += '<:b_:708663476729413693>'
                else:
                    output+= '<:w_:708663422924882051>'
            outputList.append(output)
        return outputList
    
    def update(self):
        for a in range(self.rows):
            for b in range(self.columns):
                liveNeighbours = 0
                for i in range(self.board[a][b].location[0]-1, self.board[a][b].location[0]+2):
                    if not(i < 0 or i >= self.rows):
                        for j in range(self.board[a][b].location[1]-1, self.board[a][b].location[1]+2):
                            if not(j < 0 or j >= self.columns):
                                if self.board[i][j] != self.board[a][b]:
                                    if self.board[i][j].state == 1:
                                        liveNeighbours += 1
                if self.board[a][b].state == 0 and liveNeighbours == 3:
                    self.board[a][b].nextState = 1
                elif self.board[a][b].state ==1 and (liveNeighbours < 2 or liveNeighbours > 3):
                    self.board[a][b].nextState = 0
                else:
                    self.board[a][b].nextState = self.board[a][b].state
        for a in range(self.rows):
            for b in range(self.columns):
                self.board[a][b].state = self.board[a][b].nextState


class cell:
    def __init__(self, state, location, nextState):
        self.state = state
        self.location = location
        self.nextState = nextState

def GoLsetup(rows, columns):
    board = []
    for i in range(rows):
        board.append([])
        for j in range(columns):
            board[i].append(cell(r(0,1), [i,j], 0))
    game = GoL(board, rows, columns)
    return game
bot = commands.Bot(command_prefix='!')
load_dotenv()
token = os.getenv("NzA4Mjk5NjY5MzMxMTE2MDg4.XrXjNA.3Jm_YjPlkAfCeyr2AAY3QiWOsIo")
GUILD = os.getenv('DISCORD_GUILD')
@bot.event
async def on_ready():
    print(f'{bot.user.name} has connected to Discord!')
    
@bot.command(pass_context=True, name = 'GameOfLife')
async def _GameOfLife(ctx, rows = 5, columns = 5, sleep = 5):
    rows = int(rows)
    columns = int(columns)
    sleep = int(sleep)
    msgList = [await ctx.send('Starting Game of Life, stop me with !stopGoL')]
    for i in range(rows - 1):
        msgList.append(await ctx.send('_'))
    s(5)
    global gol
    gol = True
    while gol:
        game = GoLsetup(rows, columns)
        outputList = game.findOutput()
        for i in range(rows):
            await msgList[i].edit(content = outputList[i])
        s(sleep)
        game.update()
    
@bot.command(pass_context=True, name = 'stopGoL')
async def _stopGoL(ctx):
    global gol
    gol = False

bot.run("NzA4Mjk5NjY5MzMxMTE2MDg4.XrXjNA.3Jm_YjPlkAfCeyr2AAY3QiWOsIo")
print("Hello")
