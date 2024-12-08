import { ethers } from "ethers";

const contractABI = [
    {
        "inputs": [
            {
                "internalType": "uint256",
                "name": "_ticketPrice",
                "type": "uint256"
            }
        ],
        "stateMutability": "payable",
        "type": "constructor"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "winner",
                "type": "address"
            },
            {
                "indexed": false,
                "internalType": "uint256",
                "name": "amountWon",
                "type": "uint256"
            }
        ],
        "name": "LotteryWinner",
        "type": "event"
    },
    {
        "inputs": [],
        "name": "enter",
        "outputs": [],
        "stateMutability": "payable",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "getBalance",
        "outputs": [
            {
                "internalType": "uint256",
                "name": "",
                "type": "uint256"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "getParticipants",
        "outputs": [
            {
                "internalType": "address[]",
                "name": "",
                "type": "address[]"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "isLotteryOpen",
        "outputs": [
            {
                "internalType": "bool",
                "name": "",
                "type": "bool"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "owner",
        "outputs": [
            {
                "internalType": "address",
                "name": "",
                "type": "address"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [
            {
                "internalType": "uint256",
                "name": "",
                "type": "uint256"
            }
        ],
        "name": "participants",
        "outputs": [
            {
                "internalType": "address",
                "name": "",
                "type": "address"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "pickWinner",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    },
    {
        "inputs": [
            {
                "internalType": "uint256",
                "name": "_newTicketPrice",
                "type": "uint256"
            }
        ],
        "name": "startNewLottery",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "ticketPrice",
        "outputs": [
            {
                "internalType": "uint256",
                "name": "",
                "type": "uint256"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    }
];
const contractAddress = "0x73217AA1A39917cBEB549dc8be17912508596109";

let provider, signer, lotteryContract;

// Initialize the contract
async function initialize() {
  if (!window.ethereum) {
    alert("MetaMask is required!");
    return;
  }

  provider = new ethers.BrowserProvider(window.ethereum);
  signer = await provider.getSigner();
  lotteryContract = new ethers.Contract(contractAddress, contractABI, signer);

  return { contract: lotteryContract, signer };
}

// Connect MetaMask
async function connectMetaMask() {
  if (typeof window.ethereum !== "undefined") {
    try {
      const accounts = await window.ethereum.request({ method: "eth_requestAccounts" });
      document.getElementById("walletAddress").textContent = `Connected: ${accounts[0]}`;
      await fetchTicketPrice();
    } catch (error) {
      console.error("User denied account access", error);
      alert("Please connect to MetaMask to use this app.");
    }
  } else {
    alert("MetaMask is not installed. Please install MetaMask to use this app.");
  }
}

// Fetch and display ticket price
async function fetchTicketPrice() {
  if (!lotteryContract) return;
  try {
    const ticketPrice = await lotteryContract.ticketPrice();
    document.getElementById("ticketPrice").textContent = ethers.formatEther(ticketPrice);
  } catch (error) {
    console.error("Error fetching ticket price:", error);
  }
}

// Enter the lottery
async function enterLottery() {
  if (!lotteryContract) return;
  const ticketPrice = await lotteryContract.ticketPrice();
  try {
    const transaction = await lotteryContract.enter({ value: ticketPrice });
    await transaction.wait();
    showOutput("You have successfully entered the lottery!");
  } catch (error) {
    console.error("Error entering lottery:", error);
    showOutput("Error entering lottery: " + error.message);
  }
}

// View contract balance
async function viewBalance() {
  if (!lotteryContract) return;
  try {
    const balance = await lotteryContract.getBalance();
    showOutput("Contract Balance: " + ethers.formatEther(balance) + " ETH");
  } catch (error) {
    console.error("Error fetching balance:", error);
    showOutput("Error fetching balance: " + error.message);
  }
}

// View participants
async function viewParticipants() {
  if (!lotteryContract) return;
  try {
    const participants = await lotteryContract.getParticipants();
    showOutput("Participants: " + participants.join(", "));
  } catch (error) {
    console.error("Error fetching participants:", error);
    showOutput("Error fetching participants: " + error.message);
  }
}

// Pick a winner
async function pickWinner() {
  if (!lotteryContract) return;
  try {
    const transaction = await lotteryContract.pickWinner();
    await transaction.wait();
    showOutput("Winner has been picked! Check events for details.");
  } catch (error) {
    console.error("Error picking winner:", error);
    showOutput("Error picking winner: " + error.message);
  }
}

// Utility function to display output
function showOutput(message) {
  document.getElementById("output").innerText = message;
}

// Event listeners
document.getElementById("connectMetaMask").addEventListener("click", connectMetaMask);
document.getElementById("enterLottery").addEventListener("click", enterLottery);
document.getElementById("viewBalance").addEventListener("click", viewBalance);
document.getElementById("viewParticipants").addEventListener("click", viewParticipants);
document.getElementById("pickWinner").addEventListener("click", pickWinner);

// Initialize on load
window.addEventListener("load", initialize);
