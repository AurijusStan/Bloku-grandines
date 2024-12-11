// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Lottery {
    address public owner;
    address[] public participants;

    uint public ticketPrice;
    bool public isLotteryOpen;

    event LotteryWinner(address indexed winner, uint amountWon);

    constructor(uint _ticketPrice) payable {
        owner = msg.sender;
        ticketPrice = _ticketPrice;
        isLotteryOpen = true;
    }

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can call this function");
        _;
    }

    function enter() public payable {
        require(isLotteryOpen, "The lottery is not open");
        require(msg.value == ticketPrice, "Incorrect ticket price");

        participants.push(msg.sender);
    }

    function pickWinner() public onlyOwner {
        require(isLotteryOpen, "Lottery is already closed");
        require(participants.length > 0, "No participants in the lottery");

        uint randomIndex = uint(
            keccak256(abi.encodePacked(block.timestamp, block.prevrandao, participants))
        ) % participants.length;

        address winner = participants[randomIndex];

        uint contractBalance = address(this).balance;
        uint winnerShare = (contractBalance * 60) / 100; // 60% to the winner
        uint ownerShare = contractBalance - winnerShare; // 40% to the owner

        payable(winner).transfer(winnerShare);
        payable(owner).transfer(ownerShare);

        emit LotteryWinner(winner, winnerShare);

        participants = new address[](0);
        isLotteryOpen = false;
    }

    function startNewLottery(uint _newTicketPrice) public onlyOwner {
        require(!isLotteryOpen, "The lottery is already open");

        ticketPrice = _newTicketPrice;
        isLotteryOpen = true;
    }

    function getBalance() public view returns (uint) {
        return address(this).balance;
    }

    function getParticipants() public view returns (address[] memory) {
        return participants;
    }
}
