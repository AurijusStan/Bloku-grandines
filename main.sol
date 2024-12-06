// SPDX-License-Identifier: MIT
pragma solidity 0.8.26;

contract GoodsMarketplace {
    address public seller; 
    address public buyer;
    address public courier;
    uint256 public price;
    string public description;
    bool public isSold;
    bool public isDelivered;

    event GoodsPurchased(address indexed buyer, uint256 amount, string description);
    event CourierAssigned(address indexed courier);
    event DeliveryConfirmed(address indexed buyer);
    event ExcessFundsWithdrawn(address indexed buyer, uint256 amount);

    modifier onlySeller() {
        require(msg.sender == seller, "Only seller");
        _;
    }

    modifier onlyBuyer() {
        require(msg.sender == buyer, "Only buyer");
        _;
    }

    modifier notSold() {
        require(!isSold, "Goods are already sold");
        _;
    }

    modifier onlyWhenSold() {
        require(isSold, "Goods must be sold first");
        _;
    }

    modifier notDelivered() {
        require(!isDelivered, "Goods are already delivered");
        _;
    }

    modifier onlyWhenExcessFundsExist() {
        require(address(this).balance > price, "No excess funds to withdraw");
        _;
    }

    constructor(uint256 _price, string memory _description) {
        require(_price > 0, "Price must be greater than zero");
        seller = msg.sender;
        price = _price;
        description = _description;
        isSold = false;
        isDelivered = false;
    }

    function purchaseGoods() public payable notSold {
        require(msg.value >= price, "Insufficient funds");

        buyer = msg.sender;
        isSold = true;

        emit GoodsPurchased(buyer, msg.value, description);
    }

    function assignCourier(address _courier) public onlySeller onlyWhenSold {
        require(_courier != address(0), "Invalid courier address");

        courier = _courier;

        emit CourierAssigned(courier);
    }

    function confirmDelivery() public onlyBuyer onlyWhenSold notDelivered {
        require(courier != address(0), "Courier must be assigned");

        isDelivered = true;
        payable(seller).transfer(price);

        emit DeliveryConfirmed(buyer);
    }

    function withdrawExcessFunds() public onlyBuyer onlyWhenSold onlyWhenExcessFundsExist {
        uint256 excessFunds = address(this).balance - price;

        payable(buyer).transfer(excessFunds);

        emit ExcessFundsWithdrawn(buyer, excessFunds);
    }
}
