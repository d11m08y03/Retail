import { Card, CardContent, CardHeader } from './ui/card';

interface Customer {
  name: string;
  email: string;
  phone: string;
  address: string;
  purchases: number;
}

interface CustomerCardProps {
  customer: Customer;
}

const CustomerCard: React.FC<CustomerCardProps> = ({ customer }) => {
  return (
    <Card className="bg-white shadow-md rounded-lg p-4 transition transform hover:scale-105 duration-300">
      <CardHeader>
        <h3 className="text-lg font-semibold">{customer.name}</h3>
      </CardHeader>
      <CardContent>
        <p className="text-gray-700">📧 {customer.email}</p>
        <p className="text-gray-700">📞 {customer.phone}</p>
        <p className="text-gray-700">🏠 {customer.address}</p>
        <p className="text-gray-700">💵 Purchases: {customer.purchases}</p>
      </CardContent>
    </Card>
  );
};

export default CustomerCard;
