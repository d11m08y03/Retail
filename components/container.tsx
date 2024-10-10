import React from 'react';

interface ContainerProps {
  children: React.ReactNode;
  className?: string; // Optional className for additional styling
}

const Container: React.FC<ContainerProps> = ({ children, className }) => {
  return (
    <div className={`max-w-7xl mx-auto px-4 ${className}`}>
      {children}
    </div>
  );
};

export default Container;
