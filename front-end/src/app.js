import { ethers } from "ethers";
import { BrowserProvider, Contract } from "ethers";
// import { parseEther } from "ethers";
// import { purchaseGoods, assignCourier, confirmDelivery, withdrawExcessFunds} from "./app.js";

// Expose functions to the global scope
window.purchaseGoods = purchaseGoods;
window.assignCourier = assignCourier;
window.confirmDelivery = confirmDelivery;
window.withdrawExcessFunds = withdrawExcessFunds;

// Connect to MetaMask
async function connectMetaMask() {
    if (typeof window.ethereum !== "undefined") {
        try {
            const accounts = await window.ethereum.request({ method: "eth_requestAccounts" });
            console.log("Connected account:", accounts[0]);
            document.getElementById("walletAddress").textContent = `Connected: ${accounts[0]}`;
        } catch (error) {
            console.error("User denied account access", error);
            alert("Please connect to MetaMask to use this app.");
        }
    } else {
        alert("MetaMask is not installed. Please install MetaMask to use this app.");
    }
}

window.addEventListener("load", connectMetaMask);

async function checkConnection() {
    if (typeof window.ethereum !== "undefined") {
        const accounts = await window.ethereum.request({ method: "eth_accounts" });
        if (accounts.length > 0) {
            document.getElementById("walletAddress").textContent = `Connected: ${accounts[0]}`;
        }
    }
}

window.addEventListener("load", checkConnection);

if (window.ethereum) {
    window.ethereum.on("accountsChanged", (accounts) => {
        if (accounts.length > 0) {
            document.getElementById("walletAddress").textContent = `Connected: ${accounts[0]}`;
        } else {
            document.getElementById("walletAddress").textContent = "Disconnected";
        }
    });

    window.ethereum.on("chainChanged", (chainId) => {
        console.log("Network changed to:", chainId);
        window.location.reload();
    });
}

const contractABI = [
    {
        "inputs": [
            {
                "internalType": "uint256",
                "name": "_price",
                "type": "uint256"
            },
            {
                "internalType": "string",
                "name": "_description",
                "type": "string"
            }
        ],
        "stateMutability": "nonpayable",
        "type": "constructor"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "courier",
                "type": "address"
            }
        ],
        "name": "CourierAssigned",
        "type": "event"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "buyer",
                "type": "address"
            }
        ],
        "name": "DeliveryConfirmed",
        "type": "event"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "buyer",
                "type": "address"
            },
            {
                "indexed": false,
                "internalType": "uint256",
                "name": "amount",
                "type": "uint256"
            }
        ],
        "name": "ExcessFundsWithdrawn",
        "type": "event"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "buyer",
                "type": "address"
            },
            {
                "indexed": false,
                "internalType": "uint256",
                "name": "amount",
                "type": "uint256"
            },
            {
                "indexed": false,
                "internalType": "string",
                "name": "description",
                "type": "string"
            }
        ],
        "name": "GoodsPurchased",
        "type": "event"
    },
    {
        "inputs": [
            {
                "internalType": "address",
                "name": "_courier",
                "type": "address"
            }
        ],
        "name": "assignCourier",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "buyer",
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
        "name": "confirmDelivery",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "courier",
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
        "name": "description",
        "outputs": [
            {
                "internalType": "string",
                "name": "",
                "type": "string"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "isDelivered",
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
        "name": "isSold",
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
        "name": "price",
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
        "name": "purchaseGoods",
        "outputs": [],
        "stateMutability": "payable",
        "type": "function"
    },
    {
        "inputs": [],
        "name": "seller",
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
        "name": "withdrawExcessFunds",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    }
];
const contractAddress = "0x6d3f3c0C941395faE6Ce2a6726BA285eAe6f7078";

async function initialize() {
    if (!window.ethereum) {
        alert("MetaMask is required!");
        return;
    }

    const provider = new BrowserProvider(window.ethereum);
    const signer = await provider.getSigner();
    const contract = new Contract(contractAddress, contractABI, signer);

    return { contract, signer };
}

async function purchaseGoods() {
    const { contract, signer } = await initialize();
    const priceInWei = ethers.utils.parseEther("1.0"); // Replace with actual price if dynamic
    try {
        const transaction = await contract.purchaseGoods({ value: priceInWei });
        await transaction.wait();
        alert("Goods purchased successfully!");
    } catch (error) {
        console.error(error);
        alert("Transaction failed!");
    }
}

async function assignCourier(courierAddress) {
    const { contract } = await initialize();
    try {
        const transaction = await contract.assignCourier(courierAddress);
        await transaction.wait();
        alert("Courier assigned successfully!");
    } catch (error) {
        console.error(error);
        alert("Transaction failed!");
    }
}

async function confirmDelivery() {
    const { contract } = await initialize();
    try {
        const transaction = await contract.confirmDelivery();
        await transaction.wait();
        alert("Delivery confirmed!");
    } catch (error) {
        console.error(error);
        alert("Transaction failed!");
    }
}

async function withdrawExcessFunds() {
    const { contract } = await initialize();
    try {
        const transaction = await contract.withdrawExcessFunds();
        await transaction.wait();
        alert("Excess funds withdrawn successfully!");
    } catch (error) {
        console.error(error);
        alert("Transaction failed!");
    }
}

export { purchaseGoods, assignCourier, confirmDelivery, withdrawExcessFunds};
